//
//  DetailViewController.m
//  SDKTest
//
//  Created by Martin O'Hagan on 11/12/2014.
//  Copyright (c) 2014 Atama. All rights reserved.
//

#import "DetailViewController.h"
#import <CommonCrypto/CommonCryptor.h>


@interface DetailViewController ()
@property (weak, nonatomic) IBOutlet UILabel *connectionStateLabel;
@property (weak, nonatomic) IBOutlet UILabel *signalStrengthLabel;
@property (weak, nonatomic) IBOutlet UILabel *identifierLabel;

@end

@implementation DetailViewController

#pragma mark - Managing the detail item

- (void)configureView {
    
    //ok so we have a real sesame now. lets connect to it first
    [[ATASesameManager sharedInstance] connectDevice:self.sesame withAutoReconnect:YES];
    
    [self.sesame registerConnectionStateHandler:^(ATAConnectionState connectionState) {
        [self updateLabels];
    }];
    
    [self.sesame registerSignalStrengthHandler:^(ATASignalStrength strength) {
        [self updateLabels];
    }];
    
    [self updateLabels];
}

-(void)updateLabels
{
    self.connectionStateLabel.text = [self connectionStringForEnum:self.sesame.connectionState];
    
    self.signalStrengthLabel.text = [self strengthStringForEnum:self.sesame.signalStrength];
    
    self.identifierLabel.text = self.sesame.identifier ?: @"-";
    
    //if we are connected and ready queue another update for a second later to get the identifier
    if (self.sesame.connectionState == ATAConnectionStateConnectedAndReady) {
        dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(2 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
            [self updateLabels];
        });
    }
}

-(NSString *)connectionStringForEnum:(ATAConnectionState)state
{
    switch (state) {
        case ATAConnectionStateUnknown:
            return @"Unknown";
            break;
        case ATAConnectionStateDisconnected:
            return @"Disconnected";
            break;
        case ATAConnectionStateConnectedButNotReady:
            return @"ConnectedButNotReady";
            break;
        case ATAConnectionStateConnectedAndReady:
            return @"ConnectedAndReady";
            break;
        case ATAConnectionStateConnecting:
            return @"Connecting";
            break;
        default:
            break;
    }
}

-(NSString *)strengthStringForEnum:(ATASignalStrength)strength
{
    switch (strength) {
        case ATASignalStrengthUnknown:
            return @"Unknown";
            break;
        case ATASignalStrengthWeak:
            return @"Weak";
            break;
        case ATASignalStrengthAverage:
            return @"Average";
            break;
        case ATASignalStrengthStrong:
            return @"Strong";
            break;
        case ATASignalStrengthVeryStrong:
            return @"Very Strong";
            break;
            
        default:
            return @"";
            break;
    }
}

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    [self configureView];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)pairingPressed:(id)sender
{
    [self.sesame activatePairing];
}

- (IBAction)saveSesamePressed:(id)sender
{
    [[ATASesameManager sharedInstance] saveSesame:self.sesame];
}

-(IBAction)giveChallengeKey:(id)sender
{
    NSData *keyData = [self random128BitAESKey];
    BOOL success = [self.sesame giveChallengeKey:keyData];
    if (success) {
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Success" message:@"Key set" delegate:nil cancelButtonTitle:@"Ok" otherButtonTitles:nil];
        [alert show];
    }else {
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Failure" message:@"Key was not set" delegate:nil cancelButtonTitle:@"Ok" otherButtonTitles:nil];
        [alert show];
    }
}

-(NSData *)random128BitAESKey {
    uint8_t bytes[16] = {0};
    int status = SecRandomCopyBytes(kSecRandomDefault, 16, bytes);
    if (status == -1) {
        return nil;
    }
    return [NSData dataWithBytes:bytes length:sizeof(bytes)];
}

-(IBAction)challenge:(id)sender
{
    //we need to generate another random data block and send it as the challenge
    NSData *randomData = [self random128BitAESKey];
    
    [self.sesame sendChallenge:randomData withResponse:^(BOOL success, NSError *error) {
        dispatch_async(dispatch_get_main_queue(), ^{
            if (success) {
                UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Success!" message:@"The challenge was successful" delegate:nil cancelButtonTitle:@"Ok" otherButtonTitles:nil];
                [alert show];
            }else {
                UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Failure" message:@"The challenge failed" delegate:nil cancelButtonTitle:@"Ok" otherButtonTitles:nil];
                [alert show];
            }
        });
    }];
}

@end
