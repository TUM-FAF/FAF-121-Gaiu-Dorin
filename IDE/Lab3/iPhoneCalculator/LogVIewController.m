//
//  LogVIewController.m
//  iPhoneCalculator
//
//  Created by admin on 04/09/14.
//  Copyright (c) 2014 Dorin Gaiu. All rights reserved.
//

#import "LogVIewController.h"

@interface LogVIewController ()<UITableViewDataSource,UITableViewDelegate>
- (IBAction)didTapReturn:(UIBarButtonItem *)sender;

@property (weak, nonatomic) IBOutlet UITableView *tableViewLog;
@end

@implementation LogVIewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    [self.tableViewLog reloadData];
}

- (UITableViewCell*)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"CellID"];
    cell.textLabel.text = [self.dataSource objectAtIndex:indexPath.row];
    return cell;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return self.dataSource.count;
}

- (IBAction)didTapReturn:(UIBarButtonItem *)sender
{
    [self dismissViewControllerAnimated:NO completion:nil];
}
@end
