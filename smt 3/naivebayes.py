import pandas as pd
import numpy as np

# =========================
# NAIVE BAYES GAUSSIAN
# =========================
class NaiveBayesGaussian:
    def __init__(self):
        self.classes = None
        self.mean = {}
        self.var = {}
        self.prior = {}

    def fit(self, X, y):
        self.classes = np.unique(y)

        for c in self.classes:
            X_c = X[y == c]
            self.mean[c] = np.mean(X_c, axis=0)
            self.var[c] = np.var(X_c, axis=0) + 1e-9
            self.prior[c] = len(X_c) / len(X)

    def gaussian_pdf(self, c, x):
        mean = self.mean[c]
        var = self.var[c]
        return np.exp(-(x - mean) ** 2 / (2 * var)) / np.sqrt(2 * np.pi * var)

    def predict(self, X):
        preds = []

        for x in X:
            scores = {}

            for c in self.classes:
                log_prior = np.log(self.prior[c])
                log_likelihood = np.sum(np.log(self.gaussian_pdf(c, x)))
                scores[c] = log_prior + log_likelihood

            preds.append(max(scores, key=scores.get))

        return np.array(preds)

# =========================
# BACA DATA EXCEL
# =========================
file_path = r"C:\Users\mayaa\OneDrive\Dokumen\tugas\smt 3\24081010221_Maya Aksa F.xlsx"
data = pd.read_excel(file_path)

# Kolom fitur & target
features = [
    'age','sex','cp','trestbps','chol','fbs','restecg',
    'thalach','exang','oldpeak','slope','ca','thal'
]
label = 'target'

# =========================
# PREPROCESSING
# =========================
# pastikan numerik
for col in features + [label]:
    data[col] = pd.to_numeric(data[col], errors='coerce')

# buang baris target kosong
data = data.dropna(subset=[label])

# isi NaN fitur dengan 0 (karena 0 valid)
data[features] = data[features].fillna(0)

X = data[features].values
y = data[label].values

# =========================
# TRAIN & PREDICT
# =========================
model = NaiveBayesGaussian()
model.fit(X, y)

y_pred = model.predict(X)

# =========================
# OUTPUT HASIL
# =========================
print("HASIL PREDIKSI:\n")
for i in range(len(y)):
    print(f"Baris Excel ke-{i+1}: Prediksi={int(y_pred[i])} | Aktual={int(y[i])}")

# =========================
# AKURASI
# =========================
accuracy = np.mean(y_pred == y) * 100
print(f"\nAkurasi Model: {accuracy:.2f}%")
