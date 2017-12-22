//
//  ViewController.m
//  TestApp
//
//  Created by Gulshan Mandal on 22/12/2017.
//  Copyright © 2017 Gulshan Mandal. All rights reserved.
//

#import "ViewController.h"
#import "Currency.hpp"
#include "NwImplShort.hpp"

@interface ViewController ()
@property (weak, nonatomic) IBOutlet UILabel *currencyLabel;
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    
}

void currencyConverterRateReceivied(void *sender, std::string conversionRate) {
    
    NSString *conversionRateString = [NSString stringWithCString:conversionRate.c_str()
                                       encoding:[NSString defaultCStringEncoding]];
    [(__bridge id)sender updateConversionRate:conversionRateString];
}

- (void)updateConversionRate:(NSString *)conversionRate {
    
    dispatch_async(dispatch_get_main_queue(), ^{
        self.currencyLabel.text = conversionRate;
    });
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}
- (IBAction)getCurrencyButtonTapped:(UIButton *)sender {
    
    self.currencyLabel.text = @"Loading......";
    
    dispatch_async(dispatch_get_global_queue( DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        Currency *app = new Currency(new NwImplShort());
        app->getRate((void*)CFBridgingRetain(self), &currencyConverterRateReceivied, "NOK", "INR");
    });
}


@end
