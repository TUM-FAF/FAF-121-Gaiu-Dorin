//
//  SettingsViewController.m
//  iPhoneCalculator
//
//  Created by admin on 04/09/14.
//  Copyright (c) 2014 Dorin Gaiu. All rights reserved.
//

#import "SettingsViewController.h"
NSString *const pathSettingss = @"/Users/admin/Library/Application Support/iPhone Simulator/7.1/Applications/35AE5473-4A28-462B-851D-CCB49BCB145A/Documents/Settings.plist";

@interface SettingsViewController ()
- (void)setColorForElements:(UIColor*)color;
- (IBAction)didTapCancelButton:(UIBarButtonItem *)sender;
- (IBAction)didTapSaveButton:(UIBarButtonItem *)sender;
- (IBAction)colorSwitch1:(UISwitch *)sender;
- (IBAction)colorSwitch2:(UISwitch *)sender;
@property (weak, nonatomic) IBOutlet UISwitch *colorSwitch1Outlet;
@property (weak, nonatomic) IBOutlet UISwitch *colorSwitch2Outlet;
@property (weak, nonatomic) IBOutlet UINavigationBar *topBarOutlet;
@property int currentColor;
@end

@implementation SettingsViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    NSDictionary *tempSettings = [NSDictionary dictionaryWithContentsOfFile:pathSettingss];
    NSString *tempStr = [tempSettings valueForKey:@"colorScheme"];
    int colorTemp = [tempStr intValue];
    switch(colorTemp)
    {
        case 0:
            [self.colorSwitch2Outlet setOn:NO animated:YES];
            [self.colorSwitch1Outlet setOn:YES animated:YES];
            [self setColorForElements:[UIColor orangeColor]];

            break;
        case 1:
            [self.colorSwitch1Outlet setOn:NO animated:YES];
            [self.colorSwitch2Outlet setOn:YES animated:YES];
            [self setColorForElements:[UIColor redColor]];
            break;
    }
}

- (void)setColorForElements:(UIColor*)color
{
    self.topBarOutlet.barTintColor = color;
    self.colorSwitch1Outlet.onTintColor = color;
    self.colorSwitch2Outlet.onTintColor = color;
}

- (IBAction)didTapCancelButton:(UIBarButtonItem *)sender
{
    [self.navigationController popToRootViewControllerAnimated:YES];
}

- (IBAction)colorSwitch1:(UISwitch *)sender {
    [self.colorSwitch2Outlet setOn:NO animated:YES];
    [self.colorSwitch1Outlet setOn:YES animated:YES];
    self.currentColor = 0;
    [self setColorForElements:[UIColor orangeColor]];
   
}

- (IBAction)colorSwitch2:(UISwitch *)sender {
    
    [self.colorSwitch1Outlet setOn:NO animated:YES];
    [self.colorSwitch2Outlet setOn:YES animated:YES];
    [self setColorForElements:[UIColor redColor]];
    self.currentColor = 1;
}
- (IBAction)didTapSaveButton:(UIBarButtonItem *)sender
{
    NSMutableDictionary *data = [[NSMutableDictionary alloc] init];
    [data setObject:[NSNumber numberWithInt:self.currentColor] forKey:@"colorScheme"];
    [data writeToFile:pathSettingss atomically:YES];
    [self.navigationController popToRootViewControllerAnimated:YES];
}
@end
