# <u>json-scanner</u> ~ just as cheap as me...

Hand-made scanner for JavaScript Object Notation (**JSON**). Just for FUN & LEARNING ~!

## ⟫ Example ?

Running this scanner on following test **JSON** file... :

```json
{
    "firstName": "John",
    "lastName": "Doe",
    "email": "john.doe@web.com",
    "age": 17,
    "adult": false,
    "favoriteColors: ["Red", "Green", "Blue"],
    "country": null,
    notValid: true
}
```

... will print following output in the terminal:

<details>
<summary>CLICK TO VIEW</summary>

```bash

TOKEN        |   LINE:CHAR   | TEXT
-------------+---------------+-------------
LBRACE       |      1:1      | {
-------------+---------------+-------------
STRING_KEY   |      2:5      | "firstName"
-------------+---------------+-------------
COLON        |      2:16     | :
-------------+---------------+-------------
STRING_VALUE |      2:18     | "John"
-------------+---------------+-------------
COMMA        |      2:24     | ,
-------------+---------------+-------------
STRING_KEY   |      3:5      | "lastName"
-------------+---------------+-------------
COLON        |      3:15     | :
-------------+---------------+-------------
STRING_VALUE |      3:17     | "Doe"
-------------+---------------+-------------
COMMA        |      3:22     | ,
-------------+---------------+-------------
STRING_KEY   |      4:5      | "email"
-------------+---------------+-------------
COLON        |      4:12     | :
-------------+---------------+-------------
STRING_VALUE |      4:14     | "john.doe@web.com"
-------------+---------------+-------------
COMMA        |      4:32     | ,
-------------+---------------+-------------
STRING_KEY   |      5:5      | "age"
-------------+---------------+-------------
COLON        |      5:10     | :
-------------+---------------+-------------
NUMBER       |      5:12     | 17
-------------+---------------+-------------
STRING_KEY   |      6:5      | "adult"
-------------+---------------+-------------
COLON        |      6:12     | :
-------------+---------------+-------------
FALSE        |      6:14     | false
-------------+---------------+-------------
COMMA        |      6:19     | ,
-------------+---------------+-------------
ERROR        |      7:20     | "favoriteColors <- Closing Quote is missing.
-------------+---------------+-------------
COLON        |      7:20     | :
-------------+---------------+-------------
LBRACKET     |      7:22     | [
-------------+---------------+-------------
STRING_VALUE |      7:23     | "Red"
-------------+---------------+-------------
COMMA        |      7:28     | ,
-------------+---------------+-------------
STRING_VALUE |      7:30     | "Green"
-------------+---------------+-------------
COMMA        |      7:37     | ,
-------------+---------------+-------------
STRING_VALUE |      7:39     | "Blue"
-------------+---------------+-------------
RBRACKET     |      7:45     | ]
-------------+---------------+-------------
COMMA        |      7:46     | ,
-------------+---------------+-------------
STRING_KEY   |      8:5      | "country"
-------------+---------------+-------------
COLON        |      8:14     | :
-------------+---------------+-------------
NULL         |      8:16     | null
-------------+---------------+-------------
COMMA        |      8:20     | ,
-------------+---------------+-------------
ERROR        |      9:13     | notValid <- Unknown or incomplete token.
-------------+---------------+-------------
COLON        |      9:13     | :
-------------+---------------+-------------
TRUE         |      9:15     | true
-------------+---------------+-------------
RBRACE       |     10:1      | }
-------------+---------------+-------------

```

</details>

## ⟫ Compile & Run

- Make sure `make` is installed. Following command can be used for Debian based distros to install it:

```bash
sudo apt update && sudo apt install make
```
- Compile it with the following command:

```bash
make sjson
```
- A new directory `build` will be created. `cd` into it and run `sjson` on any valid `.json` file:

```bash
cd build/
./sjson test.json
```
