# DCAlculator

**DCAlculator** is a command-line program designed to simplify mathematical calculations quickly and easily. This application leverages the powerful [exprtk](https://www.partow.net/programming/exprtk/index.html) library for performing mathematical calculations. DCAlculator is distributed under the MIT license, the same license shared with the exprtk library.

## Usage

To use DCAlculator, simply follow the command structure below:

```shell
dcalc [OPTION] [EXPRESSION]
```

## Options
`-c`, `--calculate` `<EXPRESSION>`: Calculate the result of the provided expression as "Result: [RESULT]".  
`-rc`, `--raw-calculate` `<EXPRESSION>`: Calculate the result of the expression without adding any additional text, displaying only the numeric result.  
`-h`, `--help`: Display this help message.  
`-h`, `--version`: Display the current program version.  

With no arguments it will display a simple income of data by terminal, this is, it will ask you to introduce an `EXPRESSION` and it will calculate it.

## Usage Examples

- Calculate the result of an expression:

```shell
dcalc -c "2134/(log(345)^2) * sin(23)"
```
This will provide you with the numeric result of the given mathematical expression as "Result of the expression: -52.8841".

- Calculate the result of an expression without added text:

```shell
dcalc -rc "2134/(log(345)^2) * sin(23)"
```
This will provide you with the numeric result of the given mathematical expression as "-52.8841".

- The expression can also be used as the following:

```shell
dcalc -c 45 + 6 - 56
```

> **NOTE**: Take into account that this way will not work properly with some symbols, because the terminal may interpret some symbols as special ones, so will not work properly in that case

- Calculate with user interface:

```
Enter the expression to calculate: 2134/(log(345)^2) * sin(23)
Result of the expression: -52.8841
```

DCAlculator is a versatile tool that will help you efficiently perform mathematical calculations directly from the command line.
Take advantage of its ease of use and power to quickly and accurately solve your mathematical calculations.
