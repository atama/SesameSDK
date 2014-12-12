//
//  ATASesameEnums.h
//  SesameSDK
//
//  Created by Martin O'Hagan on 05/12/2014.
//  Copyright (c) 2014 Atama. All rights reserved.
//

#ifndef SesameSDK_ATASesameEnums_h
#define SesameSDK_ATASesameEnums_h

typedef NS_ENUM(NSUInteger, ATASignalStrength) {
    ATASignalStrengthUnknown,
    ATASignalStrengthWeak,
    ATASignalStrengthAverage,
    ATASignalStrengthStrong,
    ATASignalStrengthVeryStrong
};

typedef void(^ATASignalStrengthCallback)(ATASignalStrength strength);



typedef NS_ENUM(NSUInteger, ATAConnectionState) {
    ATAConnectionStateUnknown,
    ATAConnectionStateDisconnected,
    ATAConnectionStateConnecting,
    ATAConnectionStateConnectedButNotReady,
    ATAConnectionStateConnectedAndReady
};

typedef void(^ATAConnectionStateCallback)(ATAConnectionState connectionState);




typedef void(^ATAChallengeCallback)(BOOL success, NSError *error);


typedef void(^ATASesameScanningCallback)(NSArray *foundSesame);

#ifdef DEBUG
#define SDKLog NSLog
#else
#define SDKLog
#endif

#endif
