# MFMS – Municipal Financial Management System

**Course:** PAP521S – Programming in Practice
**Group number:** __
**Language:** ANSI C (C99)

## Group Members
| Student | Name | Student No. | GitHub username | Responsibility |
|---------|------|-------------|-----------------|----------------|
| 1 |Ryan Mowes |226079821 |226079821-Mowes |Employee Management |
| 2 |Charlton Draghoender |211082066 |211082066-Draghoender | Budget Management |
| 3 |Leandro Stern |223123773 |RomeoLs7 | Supplier Management |
| 4 |Jayson Vries | 226073866|226073866-Vries | Asset Management |
| 5 |Mariaman Niizimba |2240222490 | MariamaNathalia | Reports |
| 6 |Mapenzi Chimana |223011002|DRMapz| Functions, integration and validation |
| 7 |Trevor Matange |226004821 |tmatange-lab | Testing, documentation and Git coordination |

## Project Description
A menu-driven C application that manages employees, budgets,
suppliers and municipal assets, and produces reports.

## System Features
- Employee management (add, display, search, salary calculation)
- Budget management (allocation, expenditure, remaining budget, status)
- Supplier management (add, display, search)
- Asset register (display, search)
- Reports (employee, budget, supplier, asset)
- Input validation

## Compilation Instructions
    make

(On Windows with MSYS2, use `mingw32-make`.)

## How to Run
    ./mfms          (Linux/macOS)
    mfms.exe        (Windows)

## Individual Responsibilities
See the table above. Detailed contribution records are submitted separately.

## Commit Convention
`module: what and why`, e.g. `employees: reject negative salary to keep data valid`

## Workflow
Work on your own `feature/` branch and open a pull request into `main`.
