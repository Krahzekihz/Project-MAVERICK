Here's the updated README with the Eisenhower Matrix and Calendar features added:

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
  - **Priority sorting using the Eisenhower Matrix**

- **Task States**: Manage tasks in three states:
  - Ongoing
  - Hidden
  - Complete (collapsible section to view all completed tasks)

- **Data Storage**: Store tasks in a Microsoft Access database (.accdb) and export tasks to .accdb or .txt files.

- **User-Friendly Interface**: Intuitive design for easy navigation and task management.

- **Eisenhower Matrix**:
  - Visual priority sorting using four quadrants:  
    1. **Urgent & Important** (Do it now)  
    2. **Not Urgent & Important** (Plan it)  
    3. **Urgent & Not Important** (Delegate it)  
    4. **Not Urgent & Not Important** (Delete it)  
  - Drag and drop tasks between quadrants for easy prioritization.
  - Color-coded categories (customizable in settings).

- **Calendar Integration**:
  - Calendar view for scheduling and tracking tasks.
  - Support for multiple views: 3-day, weekly, and yearly.
  - Time blocking for focused work sessions.
  - Task creation and reminders directly from the calendar.

- **Pomodoro Timer**:
  - Circular progress timer with a digital clock in the center.
  - Independent timers for stopwatch and Pomodoro sessions.
  - Customizable Pomodoro session duration, break duration, number of breaks, and total session count.
  - Desktop notifications and sound reminders (supports custom `.mp3` uploads).
  - Session logging: Tracks start time, pause/resume times, end time, session duration, number of breaks, and pauses.
  - Notes widget: Allows bullet points, bold text, and placeholder text that disappears when clicked.
  - Export notes as `.txt` files.

## Requirements

- Visual Studio
- Qt Framework
- Microsoft Access Database Engine
- C++ Compiler
- Windows Operating System

## Installation

1. **Clone the Repository**:
   ```bash
   git clone github.com/Krahzekihz/Project-MAVERICK.git
   cd task-list-qt
   ```

2. **Open the Project**:
   - Open the project in Visual Studio.

3. **Install Qt**:
   - Ensure you have the Qt framework installed. You can download it from [Qt's official website](https://www.qt.io/download).

4. **Build the Project**:
   - Build the project in Visual Studio to compile the application.

## Usage

1. **Launching the Application**:
   - Run the compiled application from Visual Studio or the output directory.

2. **Creating a Task**:
   - Input the task description, tags, due date, and reminder time.
   - Click "Add Task" to create a new task.

3. **Managing Tasks**:
   - View ongoing tasks, hidden tasks, and completed tasks in their respective sections.
   - Collapse the completed tasks section to save space.

4. **Using the Eisenhower Matrix**:
   - Drag and drop tasks into priority quadrants.
   - Sort tasks based on urgency and importance.
   - Customize quadrant colors in settings.

5. **Using the Calendar**:
   - View tasks in a 3-day, weekly, or yearly format.
   - Create tasks directly in the calendar.
   - Set reminders and time blocks for better scheduling.

6. **Using the Pomodoro Timer**:
   - Start a Pomodoro session with a customizable timer.
   - Pause, resume, or stop the session as needed.
   - View the session progress through the circular progress indicator.
   - Receive desktop notifications when a session or break ends.
   - Take notes while working and export them when needed.

7. **Exporting Tasks**:
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


