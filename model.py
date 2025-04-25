from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.linear_model import LogisticRegression
from sklearn.pipeline import Pipeline
from sklearn.model_selection import train_test_split
from sklearn.metrics import classification_report
import pickle
import re
from nltk.corpus import stopwords
from nltk.stem import WordNetLemmatizer
import nltk

nltk.download('stopwords')
nltk.download('wordnet')

# Preprocessing Function
def preprocess_text(text):
    text = re.sub(r'\W', ' ', text)  # Remove non-alphanumeric characters
    text = text.lower()
    text = text.split()
    lemmatizer = WordNetLemmatizer()
    text = [lemmatizer.lemmatize(word) for word in text if word not in stopwords.words('english')]
    return ' '.join(text)

# Preprocess Messages
messages = [preprocess_text(message) for message in messages]

# Split Data
X_train, X_test, y_train, y_test = train_test_split(messages, labels, test_size=0.2, random_state=42)

# Define Pipeline
pipeline = Pipeline([
    ('vectorizer', TfidfVectorizer(max_features=1000)),
    ('classifier', LogisticRegression(class_weight='balanced', max_iter=200))
])

# Train Model
pipeline.fit(X_train, y_train)

# Evaluate Model
y_pred = pipeline.predict(X_test)
print(classification_report(y_test, y_pred))

# Save Model
with open("fraud_model_v2.pkl", "wb") as f:
    pickle.dump(pipeline, f)
