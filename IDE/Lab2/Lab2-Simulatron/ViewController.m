//
//  ViewController.m
//  Lab2-Simulatron
//
//  Created by admin on 10/09/14.
//  Copyright (c) 2014 Dorin Gaiu. All rights reserved.
//

#import "ViewController.h"
#import "StartGameWindowController.h"

@implementation ViewController

- (void)awakeFromNib
{
    NSString *path = [[NSBundle mainBundle]pathForResource:@"star_wars_MainTheme" ofType:@"mp3"];
    NSURL *file = [NSURL URLWithString:path];
    self.audioPlayer = [[AVAudioPlayer alloc]initWithContentsOfURL:file error:nil];
    [self.audioPlayer play];
    [self.sliderOutlet setIntValue:2];
}

- (IBAction)didTapStartGame:(NSButton *)sender
{
    if(!self.startGameController)
    {
        self.startGameController = [[StartGameWindowController alloc]initWithWindowNibName:@"StartGame"];
    }
    [self.startGameController showWindow:self];
    [self.audioPlayer setVolume:0.1];
}

- (IBAction)didTapInfo:(NSButton *)sender
{
    NSRunAlertPanel(@"How to play", @"Use the control panel of your spaceship to detect and destroy alliens", @"OK", nil, nil);

}

- (IBAction)didTapQuit:(NSButton *)sender
{
    exit(0);
}

- (IBAction)soundCheckButton:(NSButton *)sender
{
    if(!self.soundFlag)
    {
        [self.audioPlayer pause];
        self.soundFlag = YES;
    }
    else
    {
        [self.audioPlayer play];
        self.soundFlag = NO;
    }
    
}

- (IBAction)sliderAction:(NSSlider *)sender
{
    switch([self.sliderOutlet intValue])
    {
        case 0:
            [self.audioPlayer pause];
            break;
        case 1:
            [self.audioPlayer play];
            [self.audioPlayer setVolume:0.3];
            break;
        case 2:
            [self.audioPlayer play];
            [self.audioPlayer setVolume:1.0];
            break;
    }

}
@end