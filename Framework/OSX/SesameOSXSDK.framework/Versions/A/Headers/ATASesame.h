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

@interface ATASesame : NSObject <NSCoding>

/**
 *  The current connection state of the Sesame device
 */
@property (nonatomic, assign) ATAConnectionState connectionState;

/**
 *  Allows you to register a block that gets called every time the connection state of a fob changes
 *
 *  @param callback the block to call
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
 *  @param callback the block to call
 */
-(void)registerSignalStrengthHandler:(ATASignalStrengthCallback)callback;
-(void)removeSignalStrengthHandler;

/**
 *  The unique identifier of the Sesame unit. If nil it may not have been retreieved yet, Cleared on disconnection
 */
@property (nonatomic, strong, readonly) NSString *identifier;

/**
 *  Allows you to give the Sesame a challenge key to test against in the future
 *
 *  @param key The key to set on the Fob. Should be 16 bytes of random data. Preferably generated with SecRandomCopyBytes or similar
 *
 *  @return YES if successul. NO on failure
 */
-(BOOL)giveChallengeKey:(NSData *)key;
/**
 *  Allows you to challenge the Sesame unit to confirm its identity
 *
 *  @param challenge The number to challenge with
 *  @param callback  The response of the challenge
 */
-(void)sendChallenge:(NSData *)challenge withResponse:(ATAChallengeCallback)callback;

/**
 *  This is a no going back method of enabling bluetooth pairing for this Sesame device, this cannot be deactivated and every device that connects to this Sesame in future will have to pair to it.
 */
-(void)activatePairing;

@end
