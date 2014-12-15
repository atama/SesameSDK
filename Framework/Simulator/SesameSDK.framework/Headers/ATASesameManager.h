//
//  ATASesameManager.h
//  SesameSDK
//
//  Created by Martin O'Hagan on 05/12/2014.
//  Copyright (c) 2014 Atama. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ATASesameEnums.h"
#import "ATASesame.h"

#if TARGET_OS_IPHONE
#import <CoreBluetooth/CoreBluetooth.h>
#else
#import <IOBluetooth/IOBluetooth.h>
#endif

/**
 The Sesame Manager is the main class of the Sesame SDK. It allows you to discover and connect to Sesame devices. It also handles the saving of Sesame devices for later use.
 */
@interface ATASesameManager : NSObject

/**
 *  Main initialization / access to the Sesame SDK
 *
 *  @return a valid instance of the Sesame Manager class
 *  @warning You should only use this initializer
 */
+(instancetype)sharedInstance;

/**
 *  Allows you to scan for Sesame devices for a given period of time
 *
 *  @param timeout  Time to scan (in seconds)
 *  @param callback The block to call after scanning has finished. Of type ATASesameScanningCallback
 *
 *  @return YES if the scan started successfully, NO means the scan couldn't be started, normally due to Bluetooth being off.
 */
-(BOOL)scanForSesameWithTimeout:(NSInteger)timeout andCallback:(ATASesameScanningCallback)callback;

/**
 *  Connects to a Sesame device so you can interact with it. You can also choose to "link" the Sesame to auto reconnect to it
 *
 *  @param sesame        The ATASesame to connect to
 *  @param autoReconnect whether to auto reconnect or not
 */
-(void)connectDevice:(ATASesame *)sesame withAutoReconnect:(BOOL)autoReconnect;

/**
 *  Disconnect from a Sesame fob, optionally force it to remove its pairing data before disconnecting
 *
 *  @param sesame       The ATASesame to disconnect from
 *  @param shouldUnpair Forces the Sesame to remove its pairing data
 */
-(void)disconnectDevice:(ATASesame *)sesame shouldUnpair:(BOOL)shouldUnpair;

/**
 *  This "bonds" a Sesame, allowing it to be retrived at any point in the future using savedSesame, this will persist accross app launches
 *
 *  @param sesame The ATASesame to "bond" with, if nil then the previous bond is broken
 */
-(void)saveSesame:(ATASesame *)sesame;

/**
 *  Allows you to retrieve the bonded Sesame device. This will load the ATASesame from disk if required. If nil, then no Sesame has been set up
 *
 *  @return the bonded ATASesame or nil if none have been set up
 */
-(ATASesame *)savedSesame;

/**
 *  Check whether bluetooth is turned off
 *
 *  @return YES if bluetooth is turned off
 */
-(BOOL)bluetoothOff;
@end
