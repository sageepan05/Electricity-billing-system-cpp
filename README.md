Automated Electricity Billing System (C++)

A console-based billing application written in C++ (Dev C++) for the Ceylon Power Company. It handles user login, meter reading entry, bill calculation and billing summaries, using C++ vectors for dynamic data storage.

Features:

Login system with a limited number of attempts (3), after which the program exits.

Meter reading entry by customer ID and reading date

New customer detection: existing customers are updated, new ones are added automatically

Bill calculation: units used x rate per unit (Rs. 12.75) plus any outstanding amount

Billing summary lookup by customer ID (last reading date, units used, amount for units, amount due, 
total to pay)

Energy-saving tips (lighting, refrigerator, AC, water heating, appliances, long-term savings)

Logout screen showing user details and date/time

Startup screen with live date, day and time

Concepts used: 
Structures (struct) for users and meter readings, std::vector for dynamic storage, Functions with prototypes, loops, switch-case and conditional logic, Input handling with cin.ignore and numeric_limits, <ctime> for date and time display

Billing logic:

Units used        = current reading - previous reading

Amount for units  = units used x 12.75

Amount due        = previous amount due + previous total to pay

Total to pay      = amount due + amount for units

Known limitations and future improvements:

Data is stored in memory only, so it is lost when the program closes. Next step: save to a file or database.

Passwords are stored in plain text in the source code. Next step: hashing and a proper user store.

User roles are stored, but all roles currently see the same menu. Next step: role-based permissions.

Only the latest reading per customer is kept. Next step: full consumption history.

Add customer details (name, address) with customer ID as the primary key

Customer logins limited to their own billing summary and energy-saving tips

Stronger input validation (for example, rejecting a current reading lower than the previous one)
