# Spam-Message-Detector
This project is a Fraud Detection System aimed at analyzing the likelihood of fraudulent behavior based on textual data (e.g., messages). It combines the power of machine learning in the backend with C programming in the frontend for real-time analysis.

Backend (Python)
The backend focuses on building a machine learning model using Python. Here's a summary:
- Preprocessing: Text data is cleaned, tokenized, and transformed using TfidfVectorizer.
- Model Training: Logistic Regression is trained to classify fraudulent messages versus legitimate ones.
- Evaluation: The model's performance is assessed through precision, recall, F1-score, etc.
- Model Saving: The trained model is serialized with pickle, allowing the frontend to utilize it for prediction.

Frontend (C)
The frontend handles real-time fraud probability analysis using a pre-defined vocabulary of fraudulent keywords and bigrams. Here's an overview:
- Dynamic Vocabulary: Contains a weighted list of keywords and phrases associated with fraudulent messages (e.g., "urgent action", "click here").
- Message Tokenization: Splits the input message into words and generates bigrams.
- Probability Calculation: Computes a fraud score using logistic regression principles, based on keyword weights and bigrams.
- User Interaction: Prompts the user for a message, calculates fraud probability, and displays warnings based on the result.

How It Works Together
1. Backend Training:
- The Python backend creates a trained model using historical text data and labels (fraud vs. legitimate).
- This trained model informs the weights used in the C frontend.

2. Frontend Analysis:
- The user enters a message, which is cleaned and tokenized.
- The fraud probability is calculated dynamically based on keyword matches and their weights.

3.Output:
- Displays whether the message is highly suspicious, possibly fraudulent, or legitimate.

Use Cases
- Fraud Detection: For identifying spam, phishing attempts, or suspicious communication.
- Email/Message Filtering: Highlights potentially unsafe content for users.
- Cybersecurity Applications: Enhances security for individuals and organizations.
By combining Python's machine learning capabilities with C's efficiency and real-time processing, this project is a robust solution for detecting fraudulent activity based on textual patterns.
