-- Thief
SELECT * FROM people WHERE passport_number =
(SELECT passport_number FROM passengers WHERE 
flight_id = (SELECT id FROM flights WHERE day = 29 AND month = 7 AND year = 2023 ORDER BY hour, minute LIMIT 1)
AND passport_number IN 
(SELECT passport_number FROM people WHERE phone_number IN
(SELECT phone_number FROM people WHERE license_plate IN
(SELECT license_plate FROM bakery_security_logs 
WHERE day = 28 AND month = 7 AND year = 2023 AND hour <= 10 AND minute <= 26)
AND id IN 
(SELECT person_id FROM bank_accounts WHERE account_number IN
(SELECT account_number FROM atm_transactions WHERE atm_location = 'Leggett Street' AND day = 28 AND month = 7 AND transaction_type = 'withdraw')))
AND phone_number IN
(SELECT caller FROM phone_calls WHERE day = 28 AND MONTH = 7 AND duration <= 60)));

SELECT * FROM flights WHERE day = 29 AND month = 7 AND year = 2023 ORDER BY hour, minute LIMIT 1
AND passport_number IN 
(SELECT passport_number FROM people WHERE phone_number IN
(SELECT phone_number FROM people WHERE license_plate IN
(SELECT license_plate FROM bakery_security_logs 
WHERE day = 28 AND month = 7 AND year = 2023 AND hour <= 10 AND minute <= 26)
AND id IN 
(SELECT person_id FROM bank_accounts WHERE account_number IN
(SELECT account_number FROM atm_transactions WHERE atm_location = 'Leggett Street' AND day = 28 AND month = 7 AND transaction_type = 'withdraw')))
AND phone_number IN
(SELECT caller FROM phone_calls WHERE day = 28 AND MONTH = 7 AND duration <= 60));