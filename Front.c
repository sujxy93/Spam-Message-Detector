#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#define MAX_WORDS 100
#define MAX_MESSAGE_LENGTH 256
#define MAX_BIGRAMS 50

typedef struct {
    char word[MAX_MESSAGE_LENGTH];
    double weight;
} VocabularyEntry;

// Dynamic vocabulary
VocabularyEntry vocabulary[MAX_WORDS] = {
    // Common Fraud Keywords
    {"congratulations", 1.5}, {"lottery", 2.3}, {"free", 1.8}, 
    {"click", 2.0}, {"verify", 2.5}, {"account", 2.4},
    {"bank", 2.1}, {"prizes", 1.9}, {"urgent", 2.7},
    {"limited", 1.7}, {"offer", 2.0}, {"winner", 2.4},
    {"action", 1.9}, {"confirm", 2.3}, {"reward", 2.1},
    {"exclusive", 1.8}, {"claim", 2.2}, {"risk", 2.5},
    {"secure", 2.4}, {"contact", 1.8}, {"approved", 2.2},
    {"bonus", 2.0}, {"special", 1.9}, {"trial", 2.3},
    {"gift", 2.4}, {"insurance", 1.8}, {"cash", 2.2},

    // Financial and Legal Terms
    {"subscription", 1.7}, {"investment", 2.5}, {"password", 2.6},
    {"login", 2.4}, {"access", 2.3}, {"payment", 2.2},
    {"balance", 1.9}, {"overdue", 2.7}, {"invoice", 2.6},
    {"credit", 2.1}, {"loan", 2.0}, {"transfer", 2.3},
    {"received", 1.9}, {"delivery", 2.4}, {"available", 1.8},
    {"support", 2.2}, {"legal", 2.5}, {"due", 2.0},
    {"attention", 2.4}, {"alert", 2.6}, {"notification", 2.3},

    // Phrases and Urgent Keywords
    {"limited offer", 2.6}, {"urgent action", 2.8}, {"exclusive deal", 2.5},
    {"verify account", 2.7}, {"immediate payment", 2.9}, {"prize claim", 2.4},
    {"click here", 2.8}, {"free trial", 2.3}, {"important notice", 2.7},
    {"urgent response", 2.8}, {"special offer", 2.4}, {"security risk", 2.6},
    {"unauthorized access", 3.0}, {"password reset", 2.9}, {"win big", 2.5},
    {"act now", 2.6}, {"secure your account", 2.9}, {"money back", 2.4},
    {"new offer", 2.3}, {"don't miss", 2.5}, {"take action", 2.7},
    {"immediate attention", 2.8}, {"last chance", 2.6}, {"limited time", 2.5},
    {"hurry up", 2.4}, {"guaranteed win", 2.7}, {"hot deal", 2.3},
    {"apply now", 2.8}, {"instant approval", 3.0}, {"pre-approved", 2.9},

    // Advanced Financial/Phishing Terms
    {"loan approved", 3.0}, {"debt clearance", 2.8}, {"account blocked", 3.1},
    {"verify identity", 3.0}, {"urgent verification", 3.1}, {"bank details", 2.7},
    {"credit score", 2.6}, {"billing update", 2.9}, {"payment failed", 3.0},
    {"secure funds", 2.8}, {"transaction alert", 3.1}, {"low balance", 2.5},
    {"overdraft", 2.7}, {"cashback offer", 2.6}, {"loan repayment", 3.0},
    {"tax refund", 2.8}, {"crypto investment", 3.0}, {"safe transaction", 2.7},

    // Common Email Scams
    {"your account", 2.4}, {"login now", 2.7}, {"payment overdue", 3.1},
    {"verify email", 2.9}, {"click to update", 2.8}, {"unusual activity", 3.2},
    {"account suspension", 3.3}, {"reset password", 2.8}, {"activity detected", 3.1},

    // Tech Support Scams
    {"system error", 3.0}, {"technical issue", 2.9}, {"fix required", 3.1},
    {"malware detected", 3.3}, {"contact support", 2.8}, {"update required", 3.0},

    // Scam Offers
    {"work from home", 2.7}, {"earn money", 2.8}, {"easy cash", 3.0},
    {"no experience needed", 2.9}, {"guaranteed profit", 3.2},
    {"fast approval", 3.0}, {"start today", 2.6}, {"be your own boss", 2.5},

    // Miscellaneous
    {"win a car", 3.0}, {"holiday package", 2.7}, {"exclusive prize", 2.8},
    {"VIP access", 2.6}, {"gift card", 2.5}, {"your chance", 2.8},
    {"luxury item", 2.9}, {"one-time deal", 3.0}, {"free upgrade", 2.6}
};


const double intercept = -2.0;
int vocab_size = 12;

// Utility to clean and normalize a word
void cleanWord(char *word) {
    for (int i = 0; word[i]; i++) {
        word[i] = tolower(word[i]);
        if (ispunct(word[i])) {
            word[i] = '\0';
            break;
        }
    }
}

// Tokenize input message into words
int tokenizeMessage(const char *message, char tokens[][MAX_MESSAGE_LENGTH]) {
    int count = 0;
    const char *delimiter = " ";
    char temp[MAX_MESSAGE_LENGTH];
    strncpy(temp, message, MAX_MESSAGE_LENGTH);
    char *token = strtok(temp, delimiter);
    while (token != NULL) {
        cleanWord(token);
        strncpy(tokens[count], token, MAX_MESSAGE_LENGTH);
        count++;
        token = strtok(NULL, delimiter);
    }
    return count;
}

// Generate bigrams from tokens
int generateBigrams(char tokens[][MAX_MESSAGE_LENGTH], int token_count, char bigrams[][MAX_MESSAGE_LENGTH]) {
    int count = 0;
    for (int i = 0; i < token_count - 1; i++) {
        snprintf(bigrams[count], MAX_MESSAGE_LENGTH, "%s %s", tokens[i], tokens[i + 1]);
        count++;
    }
    return count;
}

// Calculate fraud probability
double calculateFraudProbability(const char *message) {
    char tokens[MAX_WORDS][MAX_MESSAGE_LENGTH];
    char bigrams[MAX_BIGRAMS][MAX_MESSAGE_LENGTH];
    int token_count = tokenizeMessage(message, tokens);
    int bigram_count = generateBigrams(tokens, token_count, bigrams);

    double score = intercept;

    // Match single words
    for (int i = 0; i < token_count; i++) {
        for (int j = 0; j < vocab_size; j++) {
            if (strcasecmp(tokens[i], vocabulary[j].word) == 0) {
                score += vocabulary[j].weight;
            }
        }
    }

    // Match bigrams
    for (int i = 0; i < bigram_count; i++) {
        for (int j = 0; j < vocab_size; j++) {
            if (strcasecmp(bigrams[i], vocabulary[j].word) == 0) {
                score += vocabulary[j].weight * 1.5; // Boost weight for bigrams
            }
        }
    }

    return 1.0 / (1.0 + exp(-score));
}

int main() {
    char message[MAX_MESSAGE_LENGTH];
    printf("Enter a message to analyze: ");
    fgets(message, MAX_MESSAGE_LENGTH, stdin);
    size_t len = strlen(message);
    if (len > 0 && message[len - 1] == '\n') {
        message[len - 1] = '\0';
    }

    double fraudProbability = calculateFraudProbability(message);

    printf("\nAnalysis Results:\n");
    if (fraudProbability > 0.8) {
        printf("Warning: This message is HIGHLY suspicious. Probability: %.2f\n", fraudProbability);
    } else if (fraudProbability > 0.5) {
        printf("Caution: This message may be fraudulent. Probability: %.2f\n", fraudProbability);
    } else {
        printf("This message seems legitimate. Probability: %.2f\n", fraudProbability);
    }

    return 0;
}
