-- Keep a log of any SQL queries you execute as you solve the mystery.
.tables
.schema
SELECT description FROM crime_scene_reports WHERE day = 28 AND month = 7; 

SELECT * FROM interviews WHERE day = 28 AND month = 7 AND year = 2023;

SELECT id, hour, minute, license_plate, activity FROM bakery_security_logs WHERE day = 28 AND month = 7 AND year = 2023 ORDER BY hour, minute; 

SELECT license_plate FROM * WHERE name = 'Eugene';

SELECT * FROM atm_transactions WHERE atm_location = 'Leggett Street' AND day = 28 AND month = 7;

SELECT * FROM people WHERE id IN 
(SELECT person_id FROM bank_accounts WHERE account_number IN
(SELECT account_number FROM atm_transactions WHERE atm_location = 'Leggett Street' AND day = 28 AND month = 7));

SELECT * FROM phone_calls WHERE day = 28 AND MONTH = 7 AND duration <= 60;

-- Principal suspects
SELECT * FROM people WHERE phone_number IN
(SELECT phone_number FROM people WHERE license_plate IN
(SELECT license_plate FROM bakery_security_logs 
WHERE day = 28 AND month = 7 AND year = 2023 AND hour <= 10 AND minute <= 26)
AND id IN 
(SELECT person_id FROM bank_accounts WHERE account_number IN
(SELECT account_number FROM atm_transactions WHERE atm_location = 'Leggett Street' AND day = 28 AND month = 7 AND transaction_type = 'withdraw')))
AND phone_number IN
(SELECT caller FROM phone_calls WHERE day = 28 AND MONTH = 7 AND duration <= 60);

-- Suspect phone calls
SELECT * FROM phone_calls WHERE day = 28 AND month = 7 AND duration <= 60
AND caller IN
(SELECT phone_number FROM people WHERE phone_number IN
(SELECT phone_number FROM people WHERE license_plate IN
(SELECT license_plate FROM bakery_security_logs 
WHERE day = 28 AND month = 7 AND year = 2023 AND hour <= 10 AND minute <= 26)
AND id IN 
(SELECT person_id FROM bank_accounts WHERE account_number IN
(SELECT account_number FROM atm_transactions WHERE atm_location = 'Leggett Street' AND day = 28 AND month = 7 AND transaction_type = 'withdraw')))
AND phone_number IN
(SELECT caller FROM phone_calls WHERE day = 28 AND MONTH = 7 AND duration <= 60));

--Possible accomplices
SELECT * FROM people WHERE phone_number IN
(SELECT receiver FROM phone_calls WHERE day = 28 AND month = 7 AND duration <= 60
AND caller IN
(SELECT phone_number FROM people WHERE phone_number IN
(SELECT phone_number FROM people WHERE license_plate IN
(SELECT license_plate FROM bakery_security_logs 
WHERE day = 28 AND month = 7 AND year = 2023 AND hour <= 10 AND minute <= 26)
AND id IN 
(SELECT person_id FROM bank_accounts WHERE account_number IN
(SELECT account_number FROM atm_transactions WHERE atm_location = 'Leggett Street' AND day = 28 AND month = 7 AND transaction_type = 'withdraw')))
AND phone_number IN
(SELECT caller FROM phone_calls WHERE day = 28 AND MONTH = 7 AND duration <= 60)));

-- Flight
SELECT * FROM flights WHERE day = 29 AND month = 7 AND year = 2023 ORDER BY hour, minute LIMIT 1;
SELECT * from airports WHERE id = 4;

-- Thief's passport
SELECT passport_number FROM passengers WHERE 
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
(SELECT caller FROM phone_calls WHERE day = 28 AND MONTH = 7 AND duration <= 60));

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

-- Accomplice
SELECT * from people WHERE phone_number = '(375) 555-8161';