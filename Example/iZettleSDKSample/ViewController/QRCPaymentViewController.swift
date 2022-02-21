//
//  QRCPaymentViewController.swift
//  iZettle SDK Sample
//
//  Copyright © 2022 PayPal Inc. All rights reserved.
//

import UIKit
import iZettleSDK

@available(iOS 13, *)
class QRCPaymentViewController: UIViewController {
    
    var paymentType: IZSDKPayPalQRCAppearance?
    
    @IBOutlet weak var amountLabel: UILabel!
    @IBOutlet weak var stepper: UIStepper!
    var lastPayment: IZSDKPayPalQRCPaymentInfo?
    var lastError: Error?

    var currentAmount: Double = 10.0 {
        didSet {
            amountLabel.text = "\(currentAmount)"
        }
    }

    override func viewDidLoad() {
        super.viewDidLoad()
        amountLabel.text = "\(currentAmount)"
        stepper.value = currentAmount
        
        if let paymentType = paymentType {
            title = paymentType == .payPal ? "PayPal QRC Payment" : "Venmo QRC Payment"
        }
    }
    
    @IBAction func chargeQRC(_ sender: Any) {
        let uuid = NSUUID().uuidString
        let amount = NSDecimalNumber(string: amountLabel.text)
        
        if let paymentType = paymentType {
            iZettleSDK.shared().chargePayPalQRC(amount: amount,
                                                reference: uuid,
                                                appearance: paymentType,
                                                presentFrom: self) { paymentInfo, error in
                self.lastError = error
                self.lastPayment = paymentInfo
                self.showConsole()
            }
        } else {
            //Convenient method without `appearance` parameter that initiates PayPal QRC payment flow
            iZettleSDK.shared().chargePayPalQRC(amount: amount, reference: uuid, presentFrom: self) { paymentInfo, error in
                self.lastError = error
                self.lastPayment = paymentInfo
                self.showConsole()
            }
        }
    }

    @IBAction func refundLastPayment() {
        if let lastPayment = lastPayment {
            refund(amount: lastPayment.amount, paymentReference: lastPayment.referenceNumber)
        } else {
            let alert = UIAlertController (title: "No payments to refund", message: "Perform a successful payment to initiate a refund", preferredStyle: .alert)
            let ok = UIAlertAction(title: "Ok", style: .default, handler: nil)
            alert.addAction(ok)
            present(alert, animated: true, completion: nil)
        }
    }
    
    func refund(amount: NSDecimalNumber, paymentReference reference: String) {
        let uuid = NSUUID().uuidString
        iZettleSDK
            .shared()
            .refundPayPalQRC(amount: amount,
                             ofPayment: reference,
                             withRefundReference: uuid,
                             presentFrom: self) { paymentInfo, error in
                self.lastError = error
                self.lastPayment = paymentInfo
                self.showConsole()
            }
    }
    
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        if segue.identifier == "showConsole",
           let _ = sender as? QRCPaymentViewController,
           let consoleVC = segue.destination as? ConsoleViewController {
            if let lastError = lastError {
                consoleVC.add(toLog: lastError)
            } else {
                consoleVC.add(toLog: lastPayment)
            }
        }
    }
    
    @IBAction func amountValueChanged(_ sender: Any) {
        let stepper = sender as! UIStepper
        currentAmount = Double(stepper.value)
    }
    
    func showConsole() {
        performSegue(withIdentifier: "showConsole", sender: self)
    }
}
