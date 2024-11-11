//
//  CardPaymentViewController.swift
//  iZettle SDK Sample
//
//  Copyright © 2024 PayPal Inc. All rights reserved.
//

import UIKit
import iZettleSDK

class CardPaymentViewController: UIViewController {
    
    @IBOutlet weak var amountLabel: UILabel!
    @IBOutlet weak var stepper: UIStepper!
    @IBOutlet weak var tippingSettingsButton: UIButton!
    @IBOutlet weak var tippingSwitch: UISwitch!
    @IBOutlet weak var lastPaymentInfoToolBar: UIToolbar!
    
    private var lastPaymentInfo: iZettleSDKPaymentInfo?
    private var lastReference: String?
    private var timestamp: Date?
    private var lastError: Error?
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        tippingSettingsButton.setTitle("", for: .normal)
        amountLabel.text = "10.0"
        stepper.value = Double(amountLabel.text ?? "0") ?? 0.0
    }
    
    
    // MARK: - User Interaction
    
    @IBAction func tippingStyleValueChanged(_ sender: UISwitch) {
        
        if tippingSwitch.isOn {
            tippingSettingsButton.isEnabled = true
        } else {
            tippingSettingsButton.isEnabled = false
        }
    }
    
    
    @IBAction func tippingSettingsButtonTapped(_ sender: UIButton) {
        let tippingSettingsVC = UINavigationController(rootViewController: TippingSettingsViewController())
        present(tippingSettingsVC, animated: true)
    }
    
    @IBAction func stepperValueChanged(_ sender: UIStepper) {
        amountLabel.text = String(format: "%.1f", sender.value)
    }
    
    @IBAction func charge(_ sender: Any) {
        lastReference = makeUniqueRefrence()
        let amount = NSDecimalNumber(string: amountLabel.text)
        
        iZettleSDK.shared().charge(
            amount: amount,
            tippingConfiguration: getSelectedTippingConfiguration(),
            reference: lastReference,
            presentFrom: self
        ) { [weak self] paymentInfo, error in
            self?.lastPaymentInfo = paymentInfo
            self?.lastError = error
            self?.timestamp = Date()
            
            self?.updateLastPaymentToolbar()
            self?.showConsole()
        }
    }
    
    @IBAction func lastPaymentInfo(_ sender: Any) {
        if let lastReference {
            iZettleSDK.shared().retrievePaymentInfo(for: lastReference, presentFrom: self) { [weak self] paymentInfo, error in
                self?.lastPaymentInfo = paymentInfo
                self?.lastError = error
                self?.showConsole()
            }
        }
    }
    
    @IBAction func refundLastPayment(_ sender: Any) {
        let paymentReference = lastReference
        lastReference = makeUniqueRefrence()
        
        if let paymentReference {
            iZettleSDK.shared().refund(amount: nil, ofPayment: paymentReference, withRefundReference: lastReference, presentFrom: self) { [weak self] paymentInfo, error in
                self?.lastPaymentInfo = paymentInfo
                self?.lastError = error
                self?.showConsole()
            }
        }
        
    }
    
    // MARK: - Segue
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        if segue.identifier == "showConsole" && sender as? UIViewController ==  self {
            if let console = segue.destination as? ConsoleViewController {
                if let lastError = lastError {
                    console.add(toLog: lastError)
                } else {
                    console.add(toLog: lastPaymentInfo)
                }
            }
        }
    }
    
    // MARK: - Helpers
    private func makeUniqueRefrence() -> String {
        return UUID().uuidString
    }
    
    func getSelectedTippingConfiguration() -> IZSDKTippingConfiguration {

        guard tippingSwitch.isOn else {
            return .disabled()
        }

        let zettleReaderTippingStyle = IZZettleReaderTippingStyle(rawValue: TippingSettingsStorage.shared.zettleReaderTippingStyle) ?? .none
        let paypalReaderTippingStyle = IZPayPalReaderTippingStyle(rawValue: TippingSettingsStorage.shared.paypalReaderTippingStyle) ?? .none

        if let storedPaypalReaderPredefinedTips = TippingSettingsStorage.shared.paypalReaderPredefinedTips {
            return IZSDKTippingConfiguration(
                zettleReaderTippingStyle: zettleReaderTippingStyle,
                paypalReaderTippingStyle: paypalReaderTippingStyle,
                paypalReaderPredefinedTippingValues: IZSDKPredefinedTippingValues(
                    option1: storedPaypalReaderPredefinedTips[0],
                    option2: storedPaypalReaderPredefinedTips[1],
                    option3: storedPaypalReaderPredefinedTips[2]
                )
            )
        } else {
            return IZSDKTippingConfiguration(
                zettleReaderTippingStyle: zettleReaderTippingStyle,
                paypalReaderTippingStyle: paypalReaderTippingStyle
            )
        }
    }
    
    private func showConsole() {
        performSegue(withIdentifier: "showConsole", sender: self)
    }
    
    private func updateLastPaymentToolbar() {
        lastPaymentInfoToolBar.isHidden = !((lastPaymentInfo != nil) && ((lastPaymentInfo?.description) != nil))
        
        if !(lastPaymentInfoToolBar.isHidden), let timestamp {
            let lastPaymentBarButton = lastPaymentInfoToolBar.items?.first
            let dateFormatter = DateFormatter()
            dateFormatter.dateStyle = .none
            dateFormatter.timeStyle = .medium
            lastPaymentBarButton?.title = "Last payment, \(dateFormatter.string(from: timestamp))"
        }
    }
    
}
