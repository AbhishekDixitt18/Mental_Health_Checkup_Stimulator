// Mental Health Companion - Application Logic

// Global State
let currentUser = {
    name: '',
    age: 0,
    moodHistory: []
};

let selectedMood = null;

// Mood Configuration
const MOODS = {
    1: { name: 'Very Sad', emoji: '😢', color: '#e74c3c' },
    2: { name: 'Sad', emoji: '😔', color: '#e67e22' },
    3: { name: 'Neutral', emoji: '😐', color: '#95a5a6' },
    4: { name: 'Happy', emoji: '😊', color: '#3498db' },
    5: { name: 'Very Happy', emoji: '😄', color: '#2ecc71' }
};

// Quotes Database
const QUOTES = {
    1: [
        '"The darkest nights produce the brightest stars." - John Green',
        '"You are stronger than you think and more capable than you imagine."',
        '"Every storm runs out of rain. This too shall pass."',
        '"Your current situation is not your final destination."'
    ],
    2: [
        '"It\'s okay to not be okay. Take your time to heal."',
        '"You have been assigned this mountain to show others it can be moved."',
        '"Difficult roads often lead to beautiful destinations."',
        '"Be patient with yourself. Growth takes time."'
    ],
    3: [
        '"Today is a new day with new possibilities."',
        '"Small steps every day lead to big changes over time."',
        '"You are exactly where you need to be right now."',
        '"Balance is not something you find, it\'s something you create."'
    ],
    4: [
        '"Happiness is not by chance, but by choice."',
        '"Keep shining! Your positive energy is contagious."',
        '"Celebrate every small victory along the way."',
        '"Your smile is your superpower!"'
    ],
    5: [
        '"Joy is the best makeup. Keep glowing!"',
        '"Your happiness is a gift to the world."',
        '"Life is beautiful when you choose to see the beauty."',
        '"Spread your wings and let your happiness soar!"'
    ]
};

// Exercises Database
const EXERCISES = {
    1: [
        'Deep Breathing: Breathe in for 4 counts, hold for 4, exhale for 6. Repeat 5 times.',
        'Grounding Exercise: Name 5 things you can see, 4 you can touch, 3 you can hear, 2 you can smell, 1 you can taste.',
        'Progressive Muscle Relaxation: Tense and release each muscle group starting from your toes to your head.',
        'Mindful Walking: Take a slow 10-minute walk, focusing on each step and your surroundings.'
    ],
    2: [
        'Gratitude Practice: Write down 3 things you\'re grateful for today.',
        'Gentle Stretching: Do some light stretches for 5-10 minutes.',
        'Journaling: Write about your feelings for 10 minutes without judgment.',
        'Listen to calming music and focus on the melody for 15 minutes.'
    ],
    3: [
        'Meditation: Sit quietly and focus on your breath for 10 minutes.',
        'Nature Connection: Spend 15 minutes outdoors or looking at nature.',
        'Creative Expression: Draw, write, or create something for 20 minutes.',
        'Mindful Tea/Coffee: Slowly enjoy a warm beverage, focusing on the taste and warmth.'
    ],
    4: [
        'Energy Release: Do some jumping jacks or dance for 5 minutes.',
        'Share Joy: Call a friend or family member and share something positive.',
        'Goal Setting: Write down one small goal you\'d like to achieve this week.',
        'Appreciation Exercise: Think of someone you appreciate and why.'
    ],
    5: [
        'Celebration Dance: Put on your favorite song and dance freely!',
        'Spread Kindness: Do something nice for someone else today.',
        'Capture the Moment: Write about what\'s making you feel so good.',
        'Physical Activity: Go for a jog, bike ride, or any energetic activity you enjoy.'
    ]
};

// Support Messages
const SUPPORT_MESSAGES = {
    1: "I can see you're going through a really tough time. Remember, it's okay to feel this way, and you're not alone.",
    2: "I notice you're feeling down today. These feelings are valid, and I'm here to help you through this.",
    3: "You seem to be in a balanced state today. This is a great time for some self-reflection and gentle activities.",
    4: "It's wonderful to see you feeling good today! Let's maintain this positive energy.",
    5: "You're radiating joy today! This is fantastic - let's celebrate and share this positive energy."
};

// Initialize Application
function initializeApp() {
    loadUserData();
    updateCurrentDate();
    
    // Set up event listeners
    document.getElementById('userName').addEventListener('keypress', function(e) {
        if (e.key === 'Enter') {
            document.getElementById('userAge').focus();
        }
    });
    
    document.getElementById('userAge').addEventListener('keypress', function(e) {
        if (e.key === 'Enter') {
            startApp();
        }
    });
}

// Start Application
function startApp() {
    const name = document.getElementById('userName').value.trim();
    const age = parseInt(document.getElementById('userAge').value);
    
    if (!name) {
        alert('Please enter your name');
        return;
    }
    
    if (!age || age < 1 || age > 120) {
        alert('Please enter a valid age');
        return;
    }
    
    currentUser.name = name;
    currentUser.age = age;
    
    saveUserData();
    
    showScreen('dashboard');
    updateDashboard();
}

// Screen Navigation
function showScreen(screenId) {
    document.querySelectorAll('.screen').forEach(screen => {
        screen.classList.remove('active');
    });
    document.getElementById(screenId).classList.add('active');
}

function backToDashboard() {
    showScreen('dashboard');
    selectedMood = null;
    clearMoodSelection();
}

// Dashboard Functions
function updateDashboard() {
    document.getElementById('dashboardUserName').textContent = `Welcome, ${currentUser.name}! 👋`;
    
    // Update avatar with first letter of name
    const firstLetter = currentUser.name.charAt(0).toUpperCase();
    document.getElementById('userAvatar').textContent = firstLetter;
}

function updateCurrentDate() {
    const now = new Date();
    const options = { weekday: 'long', year: 'numeric', month: 'long', day: 'numeric' };
    const dateString = now.toLocaleDateString('en-US', options);
    const timeString = now.toLocaleTimeString('en-US', { hour: '2-digit', minute: '2-digit' });
    
    const dateElement = document.getElementById('currentDate');
    if (dateElement) {
        dateElement.textContent = `${dateString} • ${timeString}`;
    }
}

// Mood Tracking Functions
function startMoodTracking() {
    selectedMood = null;
    clearMoodSelection();
    document.getElementById('moodNotes').value = '';
    showScreen('moodTrackingScreen');
}

function selectMood(mood) {
    selectedMood = mood;
    
    // Update UI
    document.querySelectorAll('.mood-option').forEach(option => {
        option.classList.remove('selected');
    });
    
    document.querySelector(`.mood-option[data-mood="${mood}"]`).classList.add('selected');
}

function clearMoodSelection() {
    document.querySelectorAll('.mood-option').forEach(option => {
        option.classList.remove('selected');
    });
}

function saveMood() {
    if (!selectedMood) {
        alert('Please select a mood first!');
        return;
    }
    
    const notes = document.getElementById('moodNotes').value.trim();
    const timestamp = new Date().toISOString();
    
    const moodEntry = {
        mood: selectedMood,
        timestamp: timestamp,
        notes: notes
    };
    
    currentUser.moodHistory.unshift(moodEntry);
    saveUserData();
    
    // Show support screen
    showSupportScreen(selectedMood);
}

// Support Screen Functions
function showSupportScreen(mood) {
    const supportMessage = SUPPORT_MESSAGES[mood];
    const quote = getRandomItem(QUOTES[mood]);
    const exercise = getRandomItem(EXERCISES[mood]);
    
    document.getElementById('supportMessage').textContent = `${currentUser.name}, ${supportMessage}`;
    document.getElementById('inspiringQuote').textContent = quote;
    document.getElementById('calmingExercise').textContent = exercise;
    
    // Hide all exercises initially
    document.getElementById('allExercises').innerHTML = '';
    document.getElementById('allExercises').style.display = 'none';
    
    showScreen('supportScreen');
}

function showAllExercises() {
    const allExercisesDiv = document.getElementById('allExercises');
    
    if (allExercisesDiv.style.display === 'block') {
        allExercisesDiv.style.display = 'none';
        return;
    }
    
    const exercises = EXERCISES[selectedMood];
    let html = '<h3 style="color: white; margin: 30px 0 20px 0;">All Recommended Exercises</h3>';
    
    exercises.forEach((exercise, index) => {
        html += `
            <div class="exercise-item">
                <h4>Exercise ${index + 1}</h4>
                <p>${exercise}</p>
            </div>
        `;
    });
    
    allExercisesDiv.innerHTML = html;
    allExercisesDiv.style.display = 'block';
}

// History Functions
function showMoodHistory() {
    const historyContent = document.getElementById('historyContent');
    
    if (currentUser.moodHistory.length === 0) {
        historyContent.innerHTML = `
            <div class="empty-state">
                <div class="empty-state-icon">📝</div>
                <h3>No Mood Entries Yet</h3>
                <p>Start tracking your mood to see your emotional journey!</p>
            </div>
        `;
    } else {
        let html = '';
        
        currentUser.moodHistory.forEach((entry, index) => {
            const moodConfig = MOODS[entry.mood];
            const date = new Date(entry.timestamp);
            const dateString = date.toLocaleDateString('en-US', { 
                weekday: 'short', 
                year: 'numeric', 
                month: 'short', 
                day: 'numeric' 
            });
            const timeString = date.toLocaleTimeString('en-US', { 
                hour: '2-digit', 
                minute: '2-digit' 
            });
            
            html += `
                <div class="history-item">
                    <div class="history-header">
                        <div class="history-mood">
                            <div class="history-mood-emoji">${moodConfig.emoji}</div>
                            <div class="history-mood-text">${moodConfig.name}</div>
                        </div>
                        <div class="history-date">${dateString} • ${timeString}</div>
                    </div>
                    ${entry.notes ? `<div class="history-notes">💭 ${entry.notes}</div>` : ''}
                </div>
            `;
        });
        
        historyContent.innerHTML = html;
    }
    
    showScreen('historyScreen');
}

// Statistics Functions
function showStatistics() {
    const statsContent = document.getElementById('statisticsContent');
    
    if (currentUser.moodHistory.length === 0) {
        statsContent.innerHTML = `
            <div class="empty-state">
                <div class="empty-state-icon">📊</div>
                <h3>No Statistics Available</h3>
                <p>Track your mood to see insightful statistics!</p>
            </div>
        `;
    } else {
        const stats = calculateStatistics();
        let html = '<div class="stats-card"><h3 style="margin-bottom: 25px; color: #667eea;">Your Mood Distribution</h3>';
        
        Object.keys(stats).forEach(moodId => {
            const moodConfig = MOODS[moodId];
            const count = stats[moodId].count;
            const percentage = stats[moodId].percentage;
            
            html += `
                <div class="stat-item">
                    <div class="stat-left">
                        <div class="stat-emoji">${moodConfig.emoji}</div>
                        <div class="stat-label">${moodConfig.name}</div>
                    </div>
                    <div class="stat-right">
                        <div class="stat-count">${count}</div>
                        <div class="stat-percentage">${percentage.toFixed(1)}%</div>
                    </div>
                </div>
                <div class="stat-bar">
                    <div class="stat-bar-fill" style="width: ${percentage}%"></div>
                </div>
            `;
        });
        
        html += '</div>';
        
        // Add total entries card
        html += `
            <div class="stats-card">
                <h3 style="color: #667eea; margin-bottom: 15px;">Overview</h3>
                <p style="font-size: 18px; color: #555;">
                    <strong>Total Entries:</strong> ${currentUser.moodHistory.length}<br>
                    <strong>Tracking Since:</strong> ${getFirstEntryDate()}
                </p>
            </div>
        `;
        
        statsContent.innerHTML = html;
    }
    
    showScreen('statisticsScreen');
}

function calculateStatistics() {
    const stats = {};
    
    currentUser.moodHistory.forEach(entry => {
        if (!stats[entry.mood]) {
            stats[entry.mood] = { count: 0, percentage: 0 };
        }
        stats[entry.mood].count++;
    });
    
    const total = currentUser.moodHistory.length;
    Object.keys(stats).forEach(moodId => {
        stats[moodId].percentage = (stats[moodId].count / total) * 100;
    });
    
    return stats;
}

function getFirstEntryDate() {
    if (currentUser.moodHistory.length === 0) return 'N/A';
    
    const lastEntry = currentUser.moodHistory[currentUser.moodHistory.length - 1];
    const date = new Date(lastEntry.timestamp);
    return date.toLocaleDateString('en-US', { 
        year: 'numeric', 
        month: 'long', 
        day: 'numeric' 
    });
}

// Resources Screen
function showResources() {
    // Generate a random mood for inspiration
    const randomMood = Math.floor(Math.random() * 5) + 1;
    showResourcesForMood(randomMood);
}

function showResourcesForMood(mood) {
    selectedMood = mood;
    
    const quote = getRandomItem(QUOTES[mood]);
    const exercise = getRandomItem(EXERCISES[mood]);
    
    document.getElementById('supportMessage').textContent = `Daily Wellness Resources`;
    document.getElementById('inspiringQuote').textContent = quote;
    document.getElementById('calmingExercise').textContent = exercise;
    
    document.getElementById('allExercises').innerHTML = '';
    document.getElementById('allExercises').style.display = 'none';
    
    showScreen('supportScreen');
}

// User Info Modal
function showUserInfo() {
    document.getElementById('modalUserName').textContent = currentUser.name;
    document.getElementById('modalUserAge').textContent = currentUser.age;
    document.getElementById('modalTotalEntries').textContent = currentUser.moodHistory.length;
    
    document.getElementById('userInfoModal').classList.add('active');
}

function closeUserInfo() {
    document.getElementById('userInfoModal').classList.remove('active');
}

// Close modal when clicking outside
window.onclick = function(event) {
    const modal = document.getElementById('userInfoModal');
    if (event.target == modal) {
        closeUserInfo();
    }
}

// Data Persistence
function saveUserData() {
    localStorage.setItem('mentalHealthUser', JSON.stringify(currentUser));
}

function loadUserData() {
    const savedData = localStorage.getItem('mentalHealthUser');
    if (savedData) {
        currentUser = JSON.parse(savedData);
        
        // Skip welcome screen if user exists
        if (currentUser.name) {
            document.getElementById('userName').value = currentUser.name;
            document.getElementById('userAge').value = currentUser.age;
            showScreen('dashboard');
            updateDashboard();
        }
    }
}

// Utility Functions
function getRandomItem(array) {
    return array[Math.floor(Math.random() * array.length)];
}

// Initialize when page loads
window.addEventListener('DOMContentLoaded', initializeApp);

// Update date every minute
setInterval(updateCurrentDate, 60000);
