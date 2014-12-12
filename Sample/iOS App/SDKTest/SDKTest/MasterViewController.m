//
//  MasterViewController.m
//  SDKTest
//
//  Created by Martin O'Hagan on 11/12/2014.
//  Copyright (c) 2014 Atama. All rights reserved.
//

#import "MasterViewController.h"
#import "DetailViewController.h"
#import <SesameSDK/SesameSDK.h>
#import <SVProgressHUD/SVProgressHUD.h>


@interface MasterViewController ()

@property NSArray *foundSesame;

@end

@implementation MasterViewController

- (void)awakeFromNib {
    [super awakeFromNib];
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(2 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        [SVProgressHUD setBackgroundColor:[UIColor colorWithWhite:0.090 alpha:1.000]];
        [SVProgressHUD setForegroundColor:[UIColor colorWithWhite:0.926 alpha:1.000]];
        [SVProgressHUD showWithStatus:@"Scanning"];
        
        [[ATASesameManager sharedInstance] scanForSesameWithTimeout:3 andCallback:^(NSArray *foundSesame) {
            self.foundSesame = foundSesame;
            
            
            if ([[ATASesameManager sharedInstance] savedSesame]) {
                self.foundSesame = [self.foundSesame arrayByAddingObject:[[ATASesameManager sharedInstance] savedSesame]];
            }
            
            [self.tableView reloadData];
            [SVProgressHUD dismiss];
        }];
    });
    
    // Do any additional setup after loading the view, typically from a nib.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark - Segues

- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    if ([[segue identifier] isEqualToString:@"showDetail"]) {
        NSIndexPath *indexPath = [self.tableView indexPathForSelectedRow];
        ATASesame *object = self.foundSesame[indexPath.row];
        [[segue destinationViewController] setSesame:object];
    }
}

#pragma mark - Table View

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return self.foundSesame.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"Cell" forIndexPath:indexPath];

    ATASesame *object = self.foundSesame[indexPath.row];
    cell.textLabel.text = [NSString stringWithFormat:@"%@%@ %@", object == [[ATASesameManager sharedInstance] savedSesame] ? @"Saved " : @"", @"Sesame", [self strengthStringForEnum:object.signalStrength]];
    return cell;
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


@end
