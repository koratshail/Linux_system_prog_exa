#!/bin/bash

# Update package lists
echo "Updating package lists..."
sudo apt-get update

# Install essential build tools
echo "Installing build-essential, compilers, and related tools..."
sudo apt-get install -y build-essential

# Install Vim editor
echo "Installing Vim editor..."
sudo apt-get install -y vim

# Install GCC and G++
echo "Installing GCC and G++ compilers..."
sudo apt-get install -y gcc g++

# Install Clang compiler
echo "Installing Clang compiler..."
sudo apt-get install -y clang

# Install debugging tools
echo "Installing debugging tools like gdb and valgrind..."
sudo apt-get install -y gdb valgrind

# Install other useful tools
echo "Installing other useful tools like make, git, ctags, etc..."
sudo apt-get install -y make git ctags

# Install Tilix terminal emulator
echo "Installing Tilix terminal emulator..."
sudo apt-get install -y tilix

# Install libraries often used in system programming
echo "Installing common development libraries..."
sudo apt-get install -y libssl-dev libc6-dev libncurses5-dev libncursesw5-dev

# Download and install the GNU C Library (glibc) sources
echo "Installing glibc source packages..."
sudo apt-get install -y glibc-source

# Optional: Install more advanced editors (like Emacs) or other utilities
# Uncomment the following lines to install emacs
# echo "Installing Emacs..."
# sudo apt-get install -y emacs

echo "Installation of system programming tools complete."

# Additional steps or configurations can be added here if needed

