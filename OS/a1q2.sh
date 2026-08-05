#!/bin/bash

echo "Enter Employee Name:"
read name

echo "Enter Basic Salary:"
read basic

echo "Enter House Rent Allowance (HRA):"
read hra

echo "Enter Dearness Allowance (DA):"
read da

net=$(echo "$basic + $hra + $da" | bc)

echo
echo "========== Salary Slip =========="
echo "Employee Name : $name"
echo "Basic Salary  : $basic"
echo "HRA           : $hra"
echo "DA            : $da"
echo "Net Salary    : $net"
echo "================================="