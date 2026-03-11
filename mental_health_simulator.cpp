#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <algorithm>

// Forward declarations
class User;
class QuoteProvider;
class CalmingExercise;
class Assistant;

// Mood enumeration
enum class MoodType {
    VERY_SAD = 1,
    SAD = 2,
    NEUTRAL = 3,
    HAPPY = 4,
    VERY_HAPPY = 5
};

// Mood entry structure
struct MoodEntry {
    MoodType mood;
    std::string timestamp;
    std::string notes;
    
    MoodEntry(MoodType m, const std::string& time, const std::string& n = "") 
        : mood(m), timestamp(time), notes(n) {}
};

// User Information Storage Module
class User {
private:
    std::string name;
    int age;
    std::vector<MoodEntry> moodHistory;
    
public:
    User() : name(""), age(0) {}
    
    void setUserInfo(const std::string& userName, int userAge) {
        name = userName;
        age = userAge;
    }
    
    std::string getName() const { return name; }
    int getAge() const { return age; }
    
    void addMoodEntry(MoodType mood, const std::string& notes = "") {
        time_t now = time(0);
        char* timeStr = ctime(&now);
        std::string timestamp(timeStr);
        timestamp.pop_back(); // Remove newline
        
        moodHistory.push_back(MoodEntry(mood, timestamp, notes));
    }
    
    const std::vector<MoodEntry>& getMoodHistory() const {
        return moodHistory;
    }
    
    std::string moodToString(MoodType mood) const {
        switch(mood) {
            case MoodType::VERY_SAD: return "Very Sad";
            case MoodType::SAD: return "Sad";
            case MoodType::NEUTRAL: return "Neutral";
            case MoodType::HAPPY: return "Happy";
            case MoodType::VERY_HAPPY: return "Very Happy";
            default: return "Unknown";
        }
    }
};

// Quote Provider Module
class QuoteProvider {
private:
    std::map<MoodType, std::vector<std::string>> quotes;
    
public:
    QuoteProvider() {
        initializeQuotes();
    }
    
    void initializeQuotes() {
        quotes[MoodType::VERY_SAD] = {
            "\"The darkest nights produce the brightest stars.\" - John Green",
            "\"You are stronger than you think and more capable than you imagine.\"",
            "\"Every storm runs out of rain. This too shall pass.\"",
            "\"Your current situation is not your final destination.\""
        };
        
        quotes[MoodType::SAD] = {
            "\"It's okay to not be okay. Take your time to heal.\"",
            "\"You have been assigned this mountain to show others it can be moved.\"",
            "\"Difficult roads often lead to beautiful destinations.\"",
            "\"Be patient with yourself. Growth takes time.\""
        };
        
        quotes[MoodType::NEUTRAL] = {
            "\"Today is a new day with new possibilities.\"",
            "\"Small steps every day lead to big changes over time.\"",
            "\"You are exactly where you need to be right now.\"",
            "\"Balance is not something you find, it's something you create.\""
        };
        
        quotes[MoodType::HAPPY] = {
            "\"Happiness is not by chance, but by choice.\"",
            "\"Keep shining! Your positive energy is contagious.\"",
            "\"Celebrate every small victory along the way.\"",
            "\"Your smile is your superpower!\""
        };
        
        quotes[MoodType::VERY_HAPPY] = {
            "\"Joy is the best makeup. Keep glowing!\"",
            "\"Your happiness is a gift to the world.\"",
            "\"Life is beautiful when you choose to see the beauty.\"",
            "\"Spread your wings and let your happiness soar!\""
        };
    }
    
    std::string getQuote(MoodType mood) {
        if (quotes[mood].empty()) return "Stay strong and keep going!";
        
        int index = rand() % quotes[mood].size();
        return quotes[mood][index];
    }
};

// Calming Exercise Module
class CalmingExercise {
private:
    std::map<MoodType, std::vector<std::string>> exercises;
    
public:
    CalmingExercise() {
        initializeExercises();
    }
    
    void initializeExercises() {
        exercises[MoodType::VERY_SAD] = {
            "Deep Breathing: Breathe in for 4 counts, hold for 4, exhale for 6. Repeat 5 times.",
            "Grounding Exercise: Name 5 things you can see, 4 you can touch, 3 you can hear, 2 you can smell, 1 you can taste.",
            "Progressive Muscle Relaxation: Tense and release each muscle group starting from your toes to your head.",
            "Mindful Walking: Take a slow 10-minute walk, focusing on each step and your surroundings."
        };
        
        exercises[MoodType::SAD] = {
            "Gratitude Practice: Write down 3 things you're grateful for today.",
            "Gentle Stretching: Do some light stretches for 5-10 minutes.",
            "Journaling: Write about your feelings for 10 minutes without judgment.",
            "Listen to calming music and focus on the melody for 15 minutes."
        };
        
        exercises[MoodType::NEUTRAL] = {
            "Meditation: Sit quietly and focus on your breath for 10 minutes.",
            "Nature Connection: Spend 15 minutes outdoors or looking at nature.",
            "Creative Expression: Draw, write, or create something for 20 minutes.",
            "Mindful Tea/Coffee: Slowly enjoy a warm beverage, focusing on the taste and warmth."
        };
        
        exercises[MoodType::HAPPY] = {
            "Energy Release: Do some jumping jacks or dance for 5 minutes.",
            "Share Joy: Call a friend or family member and share something positive.",
            "Goal Setting: Write down one small goal you'd like to achieve this week.",
            "Appreciation Exercise: Think of someone you appreciate and why."
        };
        
        exercises[MoodType::VERY_HAPPY] = {
            "Celebration Dance: Put on your favorite song and dance freely!",
            "Spread Kindness: Do something nice for someone else today.",
            "Capture the Moment: Write about what's making you feel so good.",
            "Physical Activity: Go for a jog, bike ride, or any energetic activity you enjoy."
        };
    }
    
    std::string getExercise(MoodType mood) {
        if (exercises[mood].empty()) return "Take 5 deep breaths and smile!";
        
        int index = rand() % exercises[mood].size();
        return exercises[mood][index];
    }
    
    void displayAllExercises(MoodType mood) {
        std::cout << "\n=== Recommended Exercises for " << getMoodString(mood) << " ===\n";
        for (size_t i = 0; i < exercises[mood].size(); ++i) {
            std::cout << (i + 1) << ". " << exercises[mood][i] << "\n\n";
        }
    }
    
private:
    std::string getMoodString(MoodType mood) {
        switch(mood) {
            case MoodType::VERY_SAD: return "Very Sad Mood";
            case MoodType::SAD: return "Sad Mood";
            case MoodType::NEUTRAL: return "Neutral Mood";
            case MoodType::HAPPY: return "Happy Mood";
            case MoodType::VERY_HAPPY: return "Very Happy Mood";
            default: return "Unknown Mood";
        }
    }
};

// Assistant Module
class Assistant {
private:
    QuoteProvider quoteProvider;
    CalmingExercise exerciseProvider;
    
public:
    void provideMoodSupport(MoodType mood, User& user) {
        std::cout << "\n" << std::string(50, '=') << "\n";
        std::cout << "MOOD SUPPORT SESSION\n";
        std::cout << std::string(50, '=') << "\n";
        
        // Provide personalized message
        std::cout << "Hello " << user.getName() << "! ";
        provideMoodMessage(mood);
        
        // Provide quote
        std::cout << "\n?? Here's an inspiring quote for you:\n";
        std::cout << quoteProvider.getQuote(mood) << "\n";
        
        // Provide exercise
        std::cout << "\n?? Recommended calming exercise:\n";
        std::cout << exerciseProvider.getExercise(mood) << "\n";
        
        // Ask if they want to see more exercises
        char choice;
        std::cout << "\nWould you like to see more exercises? (y/n): ";
        std::cin >> choice;
        
        if (choice == 'y' || choice == 'Y') {
            exerciseProvider.displayAllExercises(mood);
        }
        
        std::cout << std::string(50, '=') << "\n";
    }
    
private:
    void provideMoodMessage(MoodType mood) {
        switch(mood) {
            case MoodType::VERY_SAD:
                std::cout << "I can see you're going through a really tough time. Remember, it's okay to feel this way, and you're not alone.";
                break;
            case MoodType::SAD:
                std::cout << "I notice you're feeling down today. These feelings are valid, and I'm here to help you through this.";
                break;
            case MoodType::NEUTRAL:
                std::cout << "You seem to be in a balanced state today. This is a great time for some self-reflection and gentle activities.";
                break;
            case MoodType::HAPPY:
                std::cout << "It's wonderful to see you feeling good today! Let's maintain this positive energy.";
                break;
            case MoodType::VERY_HAPPY:
                std::cout << "You're radiating joy today! This is fantastic - let's celebrate and share this positive energy.";
                break;
        }
    }
};

// Main Mood Tracker Class (API)
class MoodTracker {
private:
    User user;
    Assistant assistant;
    bool sessionActive;
    
public:
    MoodTracker() : sessionActive(false) {
        srand(time(nullptr));
    }
    
    void initialize() {
        std::cout << "\n" << std::string(60, '=') << "\n";
        std::cout << "        WELCOME TO MENTAL HEALTH SIMULATOR\n";
        std::cout << std::string(60, '=') << "\n";
        
        std::string name;
        int age;
        
        std::cout << "Please enter your name: ";
        std::getline(std::cin, name);
        
        std::cout << "Please enter your age: ";
        std::cin >> age;
        
        user.setUserInfo(name, age);
        
        std::cout << "\nHello " << name << "! Welcome to your personal mental health companion.\n";
        std::cout << "This tool is designed to help you track your mood and provide support.\n";
    }
    
    bool askToStartSession() {
        char choice;
        std::cout << "\n" << std::string(40, '-') << "\n";
        std::cout << "Would you like to start a mood tracking session? (y/n): ";
        std::cin >> choice;
        
        if (choice == 'y' || choice == 'Y') {
            sessionActive = true;
            return true;
        }
        return false;
    }
    
    void startSession() {
        if (!sessionActive) {
            std::cout << "Please start a session first!\n";
            return;
        }
        
        std::cout << "\n" << std::string(40, '-') << "\n";
        std::cout << "MOOD ASSESSMENT\n";
        std::cout << std::string(40, '-') << "\n";
        
        // Ask for current mood
        MoodType currentMood = askForMood();
        
        // Ask for additional notes
        std::string notes;
        std::cout << "\nWould you like to add any notes about how you're feeling? (optional)\n";
        std::cout << "Notes: ";
        std::cin.ignore();
        std::getline(std::cin, notes);
        
        // Store mood entry
        user.addMoodEntry(currentMood, notes);
        
        // Provide support through assistant
        assistant.provideMoodSupport(currentMood, user);
        
        std::cout << "\nMood entry saved successfully!\n";
        sessionActive = false;
    }
    
    void showMoodHistory() {
        const auto& history = user.getMoodHistory();
        
        std::cout << "\n" << std::string(60, '=') << "\n";
        std::cout << "MOOD HISTORY FOR " << user.getName() << "\n";
        std::cout << std::string(60, '=') << "\n";
        
        if (history.empty()) {
            std::cout << "No mood entries found. Start a session to begin tracking!\n";
            return;
        }
        
        for (size_t i = 0; i < history.size(); ++i) {
            const auto& entry = history[i];
            std::cout << "\n?? Entry #" << (i + 1) << "\n";
            std::cout << "Date/Time: " << entry.timestamp << "\n";
            std::cout << "Mood: " << user.moodToString(entry.mood) << "\n";
            if (!entry.notes.empty()) {
                std::cout << "Notes: " << entry.notes << "\n";
            }
            std::cout << std::string(40, '-') << "\n";
        }
        
        // Show mood statistics
        showMoodStatistics(history);
    }
    
    void showMainMenu() {
        int choice;
        
        do {
            std::cout << "\n" << std::string(40, '=') << "\n";
            std::cout << "MAIN MENU\n";
            std::cout << std::string(40, '=') << "\n";
            std::cout << "1. Start Mood Tracking Session\n";
            std::cout << "2. View Mood History\n";
            std::cout << "3. View User Information\n";
            std::cout << "4. Exit\n";
            std::cout << "\nEnter your choice (1-4): ";
            std::cin >> choice;
            
            switch (choice) {
                case 1:
                    if (askToStartSession()) {
                        startSession();
                    } else {
                        std::cout << "Session cancelled.\n";
                    }
                    break;
                case 2:
                    showMoodHistory();
                    break;
                case 3:
                    showUserInfo();
                    break;
                case 4:
                    std::cout << "\nThank you for using Mental Health Simulator!\n";
                    std::cout << "Remember: Take care of your mental health. You matter! ??\n";
                    break;
                default:
                    std::cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 4);
    }
    
private:
    MoodType askForMood() {
        int moodChoice;
        
        std::cout << "\nHow are you feeling right now?\n";
        std::cout << "1. Very Sad ??\n";
        std::cout << "2. Sad ??\n";
        std::cout << "3. Neutral ??\n";
        std::cout << "4. Happy ??\n";
        std::cout << "5. Very Happy ??\n";
        std::cout << "\nEnter your choice (1-5): ";
        std::cin >> moodChoice;
        
        while (moodChoice < 1 || moodChoice > 5) {
            std::cout << "Invalid choice. Please enter a number between 1-5: ";
            std::cin >> moodChoice;
        }
        
        return static_cast<MoodType>(moodChoice);
    }
    
    void showUserInfo() {
        std::cout << "\n" << std::string(40, '=') << "\n";
        std::cout << "USER INFORMATION\n";
        std::cout << std::string(40, '=') << "\n";
        std::cout << "Name: " << user.getName() << "\n";
        std::cout << "Age: " << user.getAge() << "\n";
        std::cout << "Total Mood Entries: " << user.getMoodHistory().size() << "\n";
    }
    
    void showMoodStatistics(const std::vector<MoodEntry>& history) {
        std::map<MoodType, int> moodCount;
        
        for (const auto& entry : history) {
            moodCount[entry.mood]++;
        }
        
        std::cout << "\n?? MOOD STATISTICS\n";
        std::cout << std::string(30, '-') << "\n";
        
        for (const auto& pair : moodCount) {
            double percentage = (static_cast<double>(pair.second) / history.size()) * 100;
            std::cout << user.moodToString(pair.first) << ": " 
                      << pair.second << " times (" 
                      << std::fixed << std::setprecision(1) << percentage << "%)\n";
        }
    }
};

// Main function
int main() {
    MoodTracker tracker;
    
    // Initialize user
    tracker.initialize();
    
    // Show main menu
    tracker.showMainMenu();
    
    return 0;
}
