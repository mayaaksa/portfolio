import pandas as pd
import numpy as np

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
            self.prior[c] = X_c.shape[0] / X.shape[0]

    def gaussian_pdf(self, c, x):
        mean = self.mean[c]
        var = self.var[c]
        return np.exp(-((x - mean) ** 2) / (2 * var)) / np.sqrt(2 * np.pi * var)

    def predict(self, X):
        predictions = []

        for x in X:
            probs = []
            for c in self.classes:
                prior = np.log(self.prior[c])
                likelihood = np.sum(np.log(self.gaussian_pdf(c, x)))
                probs.append(prior + likelihood)

            predictions.append(self.classes[np.argmax(probs)])

        return np.array(predictions)

file_path = r"C:\Users\mayaa\OneDrive\Dokumen\tugas\smt 3\24081010221_Maya Aksa F.xlsx"

# Baca data
data = pd.read_excel(file_path)
features = [
    'age','sex','cp','trestbps','chol','fbs','restecg',
    'thalach','exang','oldpeak','slope','ca','thal'
]
label = 'target'

# PREPROCESSING
data[features] = data[features].apply(pd.to_numeric, errors='coerce')
data[features] = data[features].fillna(0)

X = data[features].values
y = data[label].values

# SPLIT TANPA ACAK (BIAR SESUAI EXCEL)
split = int(0.8 * len(X))

X_train = X[:split]
X_test  = X[split:]
y_train = y[:split]
y_test  = y[split:]

# TRAIN & PREDIKSI
model = NaiveBayesGaussian()
model.fit(X_train, y_train)

y_pred = model.predict(X_test)

accuracy = np.mean(y_pred == y_test)

# OUTPUT
print("Hasil Prediksi Data Testing (Urutan Sama dengan Excel):\n")

for i in range(len(y_test)):
    print(f"Data ke-{i+1}: Prediksi={y_pred[i]} | Aktual={y_test[i]}")

print(f"\nAkurasi Model: {accuracy*100:.2f}%")