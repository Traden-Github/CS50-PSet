-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Get a general understanding of the database, its tables, and the contents therein
.schema

-- Find the crime scene report by the given time and place
SELECT * FROM crime_scene_reports
WHERE year = 2021 AND month = 7 AND day = 28 AND street = 'Humphrey Street';

-- NOTES: 10:15am, Humphrey Street bakery, three witnesses mention bakery in interview transcript

-- Find the interviews for the witnesses
SELECT * FROM interviews
WHERE transcript LIKE '%bakery%';

-- 4 interviews found, eliminate the one that tookplace before the theft

-- NOTES: Ruth: thief left bakery parking lot within 10 minutes (10:15 - 10:25), check security footage
--        Eugene: recognizes thief, saw suspect withdraw money at ATM on Leggett Street before they arrived at Emma's bakery
--        Raymond: suspect plans with accomplice to take earliest flight on 7/29, asked accomplice to get ticket

-- check security footage for cars
SELECT * FROM bakery_security_logs
WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND (minute > 14 AND minute < 26);

-- 8 license plates found, will keep in mind for later

-- try to narrow down atm transactions
SELECT * FROM atm_transactions
WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw';

-- 8 accounts found, will keep in mind for later

-- find the flight in which the criminals most likely have taken (earliest flight in 7/29)
SELECT * FROM flights WHERE origin_airport_id = (
    SELECT id FROM airports WHERE city = 'Fiftyville'
) AND year = 2021 AND month = 7 AND day = 29 ORDER BY hour LIMIT 1;

-- find the destination airport by nesting the previous query
SELECT * FROM airports WHERE id = (
    SELECT destination_airport_id FROM flights WHERE origin_airport_id = (
        SELECT id FROM airports WHERE city = 'Fiftyville'
) AND year = 2021 AND month = 7 AND day = 29 ORDER BY hour LIMIT 1
);

-- NOTES: Destination: LaGuardia Airport in New York City

-- find the phone call described by Raymond, first, see the layout of the table
SELECT * FROM phone_calls LIMIT 5;

-- duration measures in seconds, now, check for the phone call in question
SELECT * FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60;

-- 9 phone calls found, will keep in mind for later

-- display passengers from the flight
SELECT * FROM passengers WHERE flight_id = (
    SELECT id FROM flights WHERE origin_airport_id = (
        SELECT id FROM airports WHERE city = 'Fiftyville'
) AND year = 2021 AND month = 7 AND day = 29 ORDER BY hour LIMIT 1
);

-- 8 individuals found

-- Use phone number, passport number from passengers, and license plate from security to narrow suspect
SELECT * FROM people WHERE phone_number IN (
    SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60
) AND passport_number IN (
    SELECT passport_number FROM passengers WHERE flight_id = (
        SELECT id FROM flights WHERE origin_airport_id = (
            SELECT id FROM airports WHERE city = 'Fiftyville'
        ) AND year = 2021 AND month = 7 AND day = 29 ORDER BY hour LIMIT 1
    )
) AND license_plate IN (
    SELECT license_plate FROM bakery_security_logs
    WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND (minute > 14 AND minute < 26)
);

-- Suspects are Sofia, Kelsey, and Bruce

-- Use bank account to narrow further
SELECT * FROM people JOIN bank_accounts ON bank_accounts.person_id = people.id
WHERE bank_accounts.account_number IN (
    SELECT account_number FROM atm_transactions
    WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw'
) AND people.name IN (
    SELECT name FROM people WHERE phone_number IN (
        SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60
        ) AND passport_number IN (
            SELECT passport_number FROM passengers WHERE flight_id = (
                SELECT id FROM flights WHERE origin_airport_id = (
                    SELECT id FROM airports WHERE city = 'Fiftyville'
                ) AND year = 2021 AND month = 7 AND day = 29 ORDER BY hour LIMIT 1
            )
        ) AND license_plate IN (
        SELECT license_plate FROM bakery_security_logs
        WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND (minute > 14 AND minute < 26)
    )
);

-- Suspect found: Bruce

-- Find accomplice of Bruce by receiver of the call
SELECT * FROM people WHERE phone_number = (
    SELECT receiver FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60
    AND caller = (
        SELECT phone_number FROM people JOIN bank_accounts ON bank_accounts.person_id = people.id
        WHERE bank_accounts.account_number IN (
            SELECT account_number FROM atm_transactions
            WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw'
        ) AND people.name IN (
            SELECT name FROM people WHERE phone_number IN (
                SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60
            )  AND passport_number IN (
                SELECT passport_number FROM passengers WHERE flight_id = (
                    SELECT id FROM flights WHERE origin_airport_id = (
                        SELECT id FROM airports WHERE city = 'Fiftyville'
                        ) AND year = 2021 AND month = 7 AND day = 29 ORDER BY hour LIMIT 1
                    )
            ) AND license_plate IN (
                SELECT license_plate FROM bakery_security_logs
                WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND (minute > 14 AND minute < 26)
            )
        )
    )
);

-- Accomplice found: Robin
