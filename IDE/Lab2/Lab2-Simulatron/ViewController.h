//
//  ViewController.h
//  Lab2-Simulatron
//
//  Created by admin on 10/09/14.
//  Copyright (c) 2014 Dorin Gaiu. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
@class StartGameWindowController;

@interface ViewController : NSObject <AVAudioPlayerDelegate>
@property BOOL soundFlag;
@property IBOutlet NSImageView *defaultImage;
@property (weak) IBOutlet NSSlider *sliderOutlet;
@property AVAudioPlayer* audioPlayer;
@property StartGameWindowController *startGameController;
- (IBAction)didTapStartGame:(NSButton *)sender;
- (IBAction)didTapInfo:(NSButton *)sender;
- (IBAction)didTapQuit:(NSButton *)sender;
- (IBAction)soundCheckButton:(NSButton *)sender;
- (IBAction)sliderAction:(NSSlider *)sender;

@end
