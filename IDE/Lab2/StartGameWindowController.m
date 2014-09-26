//
//  StartGameWindowController.m
//  Lab2-Simulatron
//
//  Created by admin on 11/09/14.
//  Copyright (c) 2014 Dorin Gaiu. All rights reserved.
//

#import "StartGameWindowController.h"
static NSString *const enemyAttacksString = @"Enemy attacks you in:";
NSString *const redDotKey = @"Red_Dot.png";
NSString *const explosionKey = @"explosion";
NSString *const enemyShipKey = @"enemy_ship.png";

@implementation StartGameWindowController

- (void)awakeFromNib
{
    [super awakeFromNib];
    self.timer = 10;
    NSTimer *timer = [NSTimer scheduledTimerWithTimeInterval:1.0 target:self selector:@selector(tick) userInfo:nil repeats:YES];
}

- (IBAction)didTapRightButton:(NSButton *)sender
{
    self.randomVal = arc4random()%3;
    [self switchImage:self.randomVal];
}

- (IBAction)didTapCenterButton:(NSButton *)sender
{
    [self switchShip:self.scannedValue str:explosionKey];
    self.timer = 10;
    self.shipsCount++;
    [self.soundsPlayer play];
    self.shootFlag = YES;
}

- (IBAction)didTapLeftButton:(NSButton *)sender
{
    [self switchShip:self.scannedValue str:enemyShipKey];
}

- (void)switchShip:(int)scan str:(NSString*)str
{
    switch(scan)
    {
        case 0:
            self.leftShip.image = [NSImage imageNamed:str];
            break;
        case 1:
            self.centerShip.image = [NSImage imageNamed:str];
            break;
        case 2:
            self.rightShip.image = [NSImage imageNamed:str];
            break;
    }
}

- (void)tick
{
    if(self.timer == -1)
    {
        self.defaultGameImage.image = [NSImage imageNamed:explosionKey];
        self.timer = 10;
        [self playSound];
        
    }
    
    NSString *timeString = [[NSString alloc]initWithFormat:@"%d",self.timer];
    self.enemyAttacksLabel.stringValue = [NSString stringWithFormat:@"%@ %@",enemyAttacksString,timeString];
    self.timer--;
}

- (void)playSound
{
    NSString *path = [[NSBundle mainBundle]pathForResource:explosionKey ofType:@"mp3"];
    NSURL *file = [NSURL URLWithString:path];
    self.soundsPlayer = [[AVAudioPlayer alloc]initWithContentsOfURL:file error:nil];
    [self.soundsPlayer play];
}

- (void)switchImage:(int)x
{
    switch(x)
    {
        case 0:
        {
           self.leftDot.image = [NSImage imageNamed:redDotKey];
        }
            break;
        case 1:
        {
            self.centerDot.image = [NSImage imageNamed:redDotKey];
        }
            break;
        case 2:
        {
            self.rightDot.image = [NSImage imageNamed:redDotKey];
        }
            break;
    }
    self.scannedValue = x;
}
@end
