# Total amount tipping flow
The “total amount tipping flow” lets customers enter the total amount including tip directly. This tipping flow can be used when taking card payments using the Zettle SDK.
## Total amount tipping flow with the card reader
1. The card reader prompts the customer to enter the payable amount including tip.
2. The customer enters the amount payable, including tip, in the card reader.
3. The customer clicks the confirmation button.
4. “Tap/Insert card” displays on the card reader.
5. The customer taps the card on the card reader.
6. The “Approved” message displays on the card reader, followed by “Thank you”.<br> 
<br>![Total amount tipping flow steps 1-6](/Documentation/images/Total_Amount_1.png)
## Total amount tipping flow with the POS system
1. The merchant selects “Pay” in the POS user interface. 
2. The POS user interface displays the payable amount and the message “Enter amount plus tip”. 
3. The card reader prompts the customer to enter the payable amount including tip.
4. The customer enters the total amount and clicks the confirmation button.<br>
<br>![Total amount tipping flow steps 1-4](/Documentation/images/Total_Amount_2.png) 
5. The total amount to be payed and “Tap/Insert card” displays in the POS user interface.
6. “Tap/Insert card” displays on the card reader.
7. The customer taps the card on the card reader.
8. The “Approved” message displays on the card reader, followed by “Thank you”.<br>
<br>![Total amount tipping flow steps 5-8](/Documentation/images/Total_Amount_3.png)<br>
## Tipping amount is too high
There is a maximum level validation to prevent accidental or invalid entering of amounts. This can happen for example if customers enter their PIN code instead of a tip amount. If the maximum level is exceeded, the card reader will display a “Too high amount” warning message. The message will time out after three seconds.<br>
<br>![Total amount tipping flow steps 5-8](/Documentation/images/Total_Amount_4.png)<br>
## Tipping amount is too low
There is a minimum level validation to prevent accidental or invalid entering of amounts. If the tipping amount is less than the original payable amount, a “Too low amount” warning message displays. After a time out the customer can enter the total amount again.<br>
<br>![Total amount tipping flow steps 5-8](/Documentation/images/Total_Amount_5.png)<br>
