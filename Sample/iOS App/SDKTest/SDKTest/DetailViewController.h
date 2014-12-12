//
//  DetailViewController.h
//  SDKTest
//
//  Created by Martin O'Hagan on 11/12/2014.
//  Copyright (c) 2014 Atama. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <SesameSDK/SesameSDK.h>

@interface DetailViewController : UIViewController

@property (strong, nonatomic) ATASesame *sesame;
@property (weak, nonatomic) IBOutlet UILabel *detailDescriptionLabel;

@end

