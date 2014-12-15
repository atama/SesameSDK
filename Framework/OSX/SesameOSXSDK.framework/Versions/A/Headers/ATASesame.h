//
//  ATASesame.h
//  SesameSDK
//
//  Created by Martin O'Hagan on 05/12/2014.
//  Copyright (c) 2014 Atama. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ATASesameEnums.h"

#if TARGET_OS_IPHONE
#import <CoreBluetooth/CoreBluetooth.h>
#else
#import <IOBluetooth/IOBluetooth.h>
#endif

/**
 *  This is the representation of a Sesame hardware device. The properties directly represent the state of the hardware and the methods directly communicate with the hardware. Although it conforms to NSCoding, it is recommended to let the SDK handle saving for you using the [ATASesameManager saveSesame:] method
 */
@interface ATASesame : NSObject <NSCoding>

/**
 *  The current connection state of the Sesame device. One of ATAConnectionState
 */
@property (nonatomic, assign) ATAConnectionState connectionState;

/**
 *  Allows you to register a block that gets called every time the connection state of the Sesame changes
 *
 *  @param callback the block to be called. Of type ATAConnectionStateCallback
 */
-(void)registerConnectionStateHandler:(ATAConnectionStateCallback)callback;
-(void)removeConnectionStateHandler;

/**
 *  The current signal strength of the Sesame device (Unknown if not connected)
 */
@property (nonatomic, assign) ATASignalStrength signalStrength;

/**
 *  Allows you to register a block that is called whenever the Signal Strength state changes
 *
 *  @param callback the block to be called. Of type ATASignalStrengthCallback
 */
-(void)registerSignalStrengthHandler:(ATASignalStrengthCallback)callback;
-(void)removeSignalStrengthHandler;

/**
 *  Allows you to set the broadcast power of the Sesame device to any value from ATABroadcastPower
 */
@property (nonatomic, assign) ATABroadcastPower broadcastPower;

/**
 *  The unique identifier of the Sesame unit. If nil it may not have been retreieved yet, Cleared on disconnection
 */
@property (nonatomic, strong, readonly) NSString *identifier;

/**
 *  Allows you to give the Sesame a challenge key to test against in the future
 *
 *  @param key The key to set on the Fob. It should be 16 bytes of random data preferably generated with SecRandomCopyBytes or similar
 *
 *  @return YES if successul. NO on failure
 */
-(BOOL)giveChallengeKey:(NSData *)key;

/**
 *  Allows you to challenge the Sesame unit to confirm its identity
 *
 *  @param challenge The data to challenge with
 *  @param callback  The block to call when the challenge has been completed. Of type ATAChallengeCallback
 */
-(void)sendChallenge:(NSData *)challenge withResponse:(ATAChallengeCallback)callback;

/**
 *  This is a no going back method of enabling bluetooth pairing for this Sesame device, this cannot be deactivated and every device that connects to this Sesame in future will have to pair to it. 
 *  @warning Pairing data can be removed with [ATASesameManager disconnectDevice:shouldUnpair:] or by removing the battery
 */
-(void)activatePairing;

@end
