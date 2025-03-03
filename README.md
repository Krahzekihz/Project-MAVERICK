# MAVERICK: Task List / To-Do List Application with Qt Integration

Welcome to the Task List / To-Do List Application! This project is designed to help you manage your tasks efficiently using a user-friendly interface built with Qt. The application allows you to create, manage, and track your tasks with various features, including tagging, due dates, reminders, and more.

## Table of Contents

- [Features](#features)
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)
- [Contact](#contact)

## Features

- **Task Management**: Create tasks with the following attributes:
  - Task description
  - Tags for categorization
  - Due date
  - Desktop reminder (set a time before the due date)
  - Automatic timestamp for task creation
  - Priority based on the Eisenhower matrix (to be implemented later)

- **Task States**: Manage tasks in three states:
  - Ongoing
  - Hidden
  - Complete (collapsible section to view all completed tasks)

- **Data Storage**: Store tasks in a Microsoft Access database (.accdb) and export tasks to .accdb or .txt files.

- **User -Friendly Interface**: Intuitive design for easy navigation and task management.

## Requirements

- Visual Studio
- Qt Framework
- Microsoft Access Database Engine
- C++ Compiler
- Windows Operating System

## Installation

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/yourusername/task-list-qt.git
   cd task-list-qt
   ```

2. **Open the Project**:
   - Open the project in Visual Studio.

3. **Install Qt**:
   - Ensure you have the Qt framework installed. You can download it from [Qt's official website](https://www.qt.io/download).

4. **Build the Project**:
   - Build the project in Visual Studio to compile the application.

5. **Set Up Microsoft Access**:
   - Create your own .accdb file using Microsoft Access and select it from the file explorer when prompted by the application.

## Usage

1. **Launching the Application**:
   - Run the compiled application from Visual Studio or the output directory.

2. **Creating a Task**:
   - Input the task description, tags, due date, and reminder time.
   - Click "Add Task" to create a new task.

3. **Managing Tasks**:
   - View ongoing tasks, hidden tasks, and completed tasks in their respective sections.
   - Collapse the completed tasks section to save space.

4. **Exporting Tasks**:
   - Use the export feature to save your tasks to a .accdb or .txt file.

## Contributing

Contributions are welcome! If you would like to contribute to this project, please follow these steps:

1. Fork the repository.
2. Create a new branch (`git checkout -b feature/YourFeature`).
3. Make your changes and commit them (`git commit -m 'Add some feature'`).
4. Push to the branch (`git push origin feature/YourFeature`).
5. Open a pull request.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.

## Contact

Nothin yet
