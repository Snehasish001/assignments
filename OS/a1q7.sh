#!/bin/bash

echo "===== CPU Information ====="

echo "Vendor ID :"
grep "vendor_id" /proc/cpuinfo | head -1

echo

echo "Model Name :"
grep "model name" /proc/cpuinfo | head -1

echo

echo "CPU MHz :"
grep "cpu MHz" /proc/cpuinfo | head -1

echo

echo "Cache Size :"
grep "cache size" /proc/cpuinfo | head -1