//
//  ATASesameEnums.h
//  SesameSDK
//
//  Created by Martin O'Hagan on 05/12/2014.
//  Copyright (c) 2014 Atama. All rights reserved.
//

#ifndef SesameSDK_ATASesameEnums_h
#define SesameSDK_ATASesameEnums_h

/**
 *  A representation of the signal strength when connected to the ATASesame
 */
typedef NS_ENUM(NSUInteger, ATASignalStrength){
    /**
     *  The signal strength has not been established yet. You are probably not connected
     */
    ATASignalStrengthUnknown,
    /**
     *  Weak signal strength (the lowest)
     */
    ATASignalStrengthWeak,
    /**
     *  Average signal strength
     */
    ATASignalStrengthAverage,
    /**
     *  Strong signal strength
     */
    ATASignalStrengthStrong,
    /**
     *  Very strong signal strength (the highest)
     */
    ATASignalStrengthVeryStrong
};

/**
 *  Callback when the signal strength is updated within the SDK
 *
 *  @param strength The updated signal strength. One of ATASignalStrength
 */
typedef void(^ATASignalStrengthCallback)(ATASignalStrength strength);


/**
 *  The bluetooth connection state of the ATASesame device
 */
typedef NS_ENUM(NSUInteger, ATAConnectionState){
    /**
     *  The connection state is unknown, probably becuase it has just been loaded from a file
     */
    ATAConnectionStateUnknown,
    /**
     *  The ATASesame is currently disconnected
     */
    ATAConnectionStateDisconnected,
    /**
     *  The ATASesame is in the process of connecting. This means a connection request to the sesame currently exists
     */
    ATAConnectionStateConnecting,
    /**
     *  The ATASesame is connected, but not yet ready to interact with. It will transition to ATAConnectionStateConnectedAndReady shortly
     */
    ATAConnectionStateConnectedButNotReady,
    /**
     *  The ATASesame is connected and ready to be interacted with.
     */
    ATAConnectionStateConnectedAndReady
};

/**
 *  The broadcast power of the ATASesame This affects the range at which a connection will be successful and stay active
 */
typedef NS_ENUM(NSUInteger, ATABroadcastPower){
    /**
     *  Broadcast power unknown, it will be read after connection
     */
    ATABroadcastPowerUnknown,
    /**
     *  Low power. This will give the shortest bluetooth range
     */
    ATABroadcastPowerLow,
    /**
     *  Average power. This will give a medium range
     */
    ATABroadcastPowerAverage,
    /**
     *  High Power. This will give the largest range
     */
    ATABroadcastPowerHigh
};

/**
 *  A block that is called when the connection state of the ATASesame changes
 *
 *  @param connectionState The new connection state. Of type ATAConnectionState
 */
typedef void(^ATAConnectionStateCallback)(ATAConnectionState connectionState);

/**
 *  A block that is called when the challenge has been completed
 *
 *  @param success a BOOL indicating success or failure
 *  @param error   An error object. Only present on failure
 */
typedef void(^ATAChallengeCallback)(BOOL success, NSError *error);

/**
 *  A block called after scanning has timed out
 *
 *  @param foundSesame An array of ATASesame objects, or nil if nothing was found
 */
typedef void(^ATASesameScanningCallback)(NSArray *foundSesame);

#endif
