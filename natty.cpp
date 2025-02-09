#include <cstdlib>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

#include <sys/wait.h>
#include <unistd.h>

std::vector<std::string> split_command(const std::string& cmd) {
  std::vector<std::string> args;
  std::stringstream ss(cmd);
  std::string arg;

  while (ss >> arg) {
    args.push_back(arg);
  }

  return args;
}

void execute_command(const std::vector<std::string>& args) {
  if (args.empty()) return;

  // Build up the command for execvp
  std::vector<char*> cargs;
  for (const auto& arg : args) {
    cargs.push_back(const_cast<char*>(arg.c_str()));
  }
  cargs.push_back(nullptr);

  pid_t pid = fork();

  if (pid == -1) {
    std::cerr << "Fork failed" << std::endl;
    return;
  }

  if (pid == 0) {  // Child process
    execvp(cargs[0], cargs.data());
    // If execvp returns, there was an error
    std::cerr << "Command not found: " << args[0] << std::endl;
    exit(1);
  } else {  // Parent process
    int status;
    waitpid(pid, &status, 0);
  }
}

std::string get_current_directory() {
  char buff[PATH_MAX];
  if (getcwd(buff, PATH_MAX) != nullptr) {
    return std::string(buff);
  }
  return "???";
}

int main() {
  std::string input;

  while (true) {
    // Display prompt
    std::cout << get_current_directory() << "$ ";

    // Get input
    std::getline(std::cin, input);

    // Check for exit command
    if (input == "exit" || input == "quit") {
      break;
    }

    // Handle cd command specially
    std::vector<std::string> args = split_command(input);
    if (!args.empty() && args[0] == "cd") {
      if (args.size() > 1) {
        if (chdir(args[1].c_str()) != 0) {
          std::cerr << "cd: No such directory: " << args[1] << std::endl;
        }
      }
      continue;
    }

    // Execute the command
    execute_command(args);
  }
}
