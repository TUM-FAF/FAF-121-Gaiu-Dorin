//
//  ViewController.m
//  iPhoneCalculator
//
//  Created by admin on 03/09/14.
//  Copyright (c) 2014 Dorin Gaiu. All rights reserved.
//

#import "ViewController.h"
#import "LogVIewController.h"
#import "SettingsViewController.h"

NSString *const pathSettings = @"/Users/admin/Library/Application Support/iPhone Simulator/7.1/Applications/35AE5473-4A28-462B-851D-CCB49BCB145A/Documents/Settings.plist";
NSString *const backgroundColorKey = @"backgroundColor";
const int maxLength = 18;

@interface ViewController ()
@property unsigned int operatorType;
@property NSDecimalNumber *firstNumber,*secondNumber,*resultNumber;
@property BOOL flagInit,flagOperator,flagEqual;
@property BOOL flagDot;
@property (weak, nonatomic) IBOutlet UILabel *calculatorDisplay;
- (IBAction)didTapEqual:(UIButton *)sender;
- (IBAction)didTapOperator:(UIButton *)sender;
- (IBAction)didTapNumber:(UIButton *)sender;
- (IBAction)didTapClear:(UIButton *)sender;
- (IBAction)didTapDot:(UIButton *)sender;
- (IBAction)didTapInfoButton:(UIButton *)sender;
@property (strong, nonatomic) IBOutlet UISwipeGestureRecognizer *swipeUpProperty;
@property (strong, nonatomic) IBOutlet UISwipeGestureRecognizer *swipeRightSettings;
- (IBAction)swRightSettings:(UISwipeGestureRecognizer *)sender;
@property (strong, nonatomic) IBOutletCollection(UIButton) NSArray *operatorsOutlet;
@property (strong, nonatomic) IBOutletCollection(UIButton) NSArray *numbersOutlet;
@property NSMutableArray *operationsArray;
@end

@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    self.operationsArray = [[NSMutableArray alloc]init];
    // gesture recognizers
    [self.swipeUpProperty setDirection:UISwipeGestureRecognizerDirectionUp];
    [self.swipeRightSettings setDirection:UISwipeGestureRecognizerDirectionLeft];
    [self.view addGestureRecognizer:self.swipeRightSettings];
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:YES];
    NSMutableDictionary *tempSettings = [[NSMutableDictionary alloc]initWithContentsOfFile:pathSettings];
    NSString *tempStr = [tempSettings valueForKey:@"colorScheme"];
    int colorTemp = [tempStr intValue];
    switch(colorTemp)
    {
        case 0:
            [self.operatorsOutlet setValue:[UIColor orangeColor] forKey:backgroundColorKey];
            [self.numbersOutlet setValue:[UIColor lightGrayColor] forKey:backgroundColorKey];
            break;
        case 1:
            [self.operatorsOutlet setValue:[UIColor redColor] forKey:backgroundColorKey];
            [self.numbersOutlet setValue:[UIColor whiteColor] forKey:backgroundColorKey];
            break;
    }
}

- (IBAction)didTapNumber:(UIButton *)sender
{
    if(!self.flagInit)
    {
        self.calculatorDisplay.text = sender.titleLabel.text;
        self.flagInit = YES;
        self.flagOperator = NO;
        return;
    }
    self.calculatorDisplay.text = [NSString stringWithFormat:@"%@%@",self.calculatorDisplay.text,sender.titleLabel.text];
}

- (IBAction)didTapClear:(UIButton *)sender
{
    self.calculatorDisplay.text = @"0";
    self.flagInit = NO;
    self.flagDot = NO;
    self.flagOperator = NO;
    self.flagEqual = NO;
    self.firstNumber = 0;
    self.secondNumber = 0;
}

- (IBAction)didTapDot:(UIButton *)sender
{
    if(!self.flagDot && self.calculatorDisplay.text.length>0)
    {
        self.flagDot = YES;
        self.flagInit = YES;
        self.calculatorDisplay.text = [NSString stringWithFormat:@"%@.",self.calculatorDisplay.text];
    }
}

- (IBAction)didTapInfoButton:(UIButton *)sender
{
    UIAlertView *infoMessage = [[UIAlertView alloc]initWithTitle:@"App Info" message:@"Created by Dorin Gaiu , 2014 , FAF-121 Rulz" delegate:nil cancelButtonTitle:@"Dismiss" otherButtonTitles:nil, nil];
    [infoMessage show];
}

- (IBAction)didTapOperator:(UIButton *)sender
{
    if(!self.flagOperator)
    {
        int tempVar = [sender.titleLabel.text characterAtIndex:0];
        switch(tempVar)
        {
            case 43:
                self.operatorType = 1; // +
                break;
            case 45:
                self.operatorType = 2; // -
                break;
            case 88:
                self.operatorType = 3; // *
                break;
            case 47:
                self.operatorType = 4; // /
                break;
            case 37:
                self.operatorType = 5; // %
                break;
            case 94:
                self.operatorType = 6;
                break;
        }
    
    self.firstNumber = [NSDecimalNumber decimalNumberWithString:self.calculatorDisplay.text];
    self.calculatorDisplay.text = @"";
    self.flagDot = NO;
    self.flagOperator = YES;
    self.flagEqual = YES;
    }
}

- (IBAction)didTapEqual:(UIButton *)sender
{
    if(self.flagEqual)
    {
        NSString *tempOperatorString;
    self.secondNumber = [NSDecimalNumber decimalNumberWithString:self.calculatorDisplay.text];
        if(self.secondNumber==nil || [self.secondNumber.stringValue isEqualToString:@"NaN"])
        {
            [self didTapClear:nil];
            return;
        }
        
        switch(self.operatorType)
        {
            case 1:
                self.resultNumber = [self.firstNumber decimalNumberByAdding:self.secondNumber];
                tempOperatorString = @"+";
                break;
            case 2:
                self.resultNumber = [self.firstNumber decimalNumberBySubtracting:self.secondNumber];
                tempOperatorString = @"-";
                break;
            case 3:
                self.resultNumber = [self.firstNumber decimalNumberByMultiplyingBy:self.secondNumber];
                tempOperatorString = @"*";
                break;
            case 4:
            {
                tempOperatorString = @"/";
                if([self.secondNumber integerValue]!=0)
                {
                    self.resultNumber = [self.firstNumber decimalNumberByDividingBy:self.secondNumber];
                }
                else
                {
                    self.flagInit = NO;
                    self.calculatorDisplay.text = @"NaN";
                    self.flagOperator = YES;
                    self.flagEqual = NO;
                    return;
                }
                
                break;
            }
            case 5:
            {
                self.resultNumber = [self.firstNumber decimalNumberByMultiplyingBy:self.secondNumber];
                NSDecimalNumber *tempNum = [NSDecimalNumber decimalNumberWithString:@"100"];
                self.resultNumber = [self.resultNumber decimalNumberByDividingBy:tempNum];
                tempOperatorString = @"%";
                break;
            }
            case 6:
                self.resultNumber = [self.firstNumber decimalNumberByRaisingToPower:self.secondNumber.integerValue];
                tempOperatorString = @"^";
                break;
        }
        
        int currentResultLength = self.resultNumber.stringValue.length;
        if(currentResultLength>18)
        {
            self.calculatorDisplay.text = [self.resultNumber.stringValue substringToIndex:maxLength];
        }
        else
        {
            self.calculatorDisplay.text = self.resultNumber.stringValue;
        }
    self.flagOperator = NO;
    self.flagEqual = NO;
    self.flagInit = NO;
        //ZzZzZ
        NSString *tempArrayData = [NSString stringWithFormat:@"%@ %@ %@ = %@",self.firstNumber.stringValue,tempOperatorString,
                                   self.secondNumber.stringValue,self.resultNumber.stringValue];
        [self.operationsArray addObject:tempArrayData];
    }
}

- (IBAction)swRightSettings:(UISwipeGestureRecognizer *)sender
{
    SettingsViewController *vc = [[SettingsViewController alloc]init];
    UIStoryboard *storyboard = [UIStoryboard storyboardWithName:@"Main" bundle:nil];
    vc = [storyboard instantiateViewControllerWithIdentifier:@"SettingsViewController"];
    [self.navigationController pushViewController:vc animated:YES];
}

- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
        LogVIewController *vc = [segue destinationViewController];
        vc.dataSource = [[NSMutableArray alloc]initWithArray:self.operationsArray];
}


@end
