//
//  StartGameWindowController.h
//  Lab2-Simulatron
//
//  Created by admin on 11/09/14.
//  Copyright (c) 2014 Dorin Gaiu. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <AVFoundation/AVFoundation.h>

@interface StartGameWindowController : NSWindowController
@property IBOutlet NSImageView *leftShip;
@property IBOutlet NSImageView *centerShip;
@property IBOutlet NSImageView *rightShip;
@property IBOutlet NSImageView *rightDot;
@property IBOutlet NSImageView *centerDot;
@property IBOutlet NSImageView *leftDot;
@property (weak) IBOutlet NSImageView *defaultGameImage;
@property (weak) IBOutlet NSTextField *shipDisplayLabel;
@property (weak) IBOutlet NSTextField *shipsDestroyedLabel;
@property (weak) IBOutlet NSTextField *enemyAttacksLabel;
@property int timer,shipsCount,randomVal,scannedValue;
@property AVAudioPlayer* soundsPlayer;
@property BOOL aimFlag,shootFlag;
- (IBAction)didTapRightButton:(NSButton *)sender;
- (IBAction)didTapCenterButton:(NSButton *)sender;
- (IBAction)didTapLeftButton:(NSButton *)sender;
- (void)playSound;
- (void)switchImage:(int)x;
- (void)switchShip:(int)scan str:(NSString*)str;
@end
