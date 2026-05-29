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

            # proteksi kalau data kosong
            if len(X_c) == 0:
                continue

            self.mean[c] = X_c.mean(axis=0)
            self.var[c]  = X_c.var(axis=0) + 1e-9
            self.prior[c] = len(X_c) / len(X)

    def gaussian_pdf(self, c, x):
        mean = self.mean[c]
        var  = self.var[c]
        return np.exp(-(x - mean)**2 / (2 * var)) / np.sqrt(2 * np.pi * var)

    def predict(self, X):
        hasil = []

        for x in X:
            posterior = {}
            for c in self.classes:
                log_prior = np.log(self.prior[c])
                log_likelihood = np.sum(np.log(self.gaussian_pdf(c, x)))
                posterior[c] = log_prior + log_likelihood

            hasil.append(max(posterior, key=posterior.get))

        return np.array(hasil)

# =========================
# BACA FILE EXCEL
# =========================
file_path = r"C:\Users\mayaa\Downloads\UAS STATKOM.xlsx"

train_df = pd.read_excel("UAS STATKOM.xlsx", sheet_name="Data Training")
test_df = pd.read_excel("UAS STATKOM.xlsx", sheet_name="data testing")

# =========================
# FITUR & LABEL
# =========================
features = [
    'age','sex','cp','trestbps','chol','fbs','restecg',
    'thalach','exang','oldpeak','slope','ca','thal'
]
label = 'target'

# =========================
# PREPROCESSING
# =========================
for col in features:
    train_df[col] = pd.to_numeric(train_df[col], errors='coerce').fillna(0)
    test_df[col]  = pd.to_numeric(test_df[col], errors='coerce').fillna(0)

train_df[label] = train_df[label].astype(int)
test_df[label]  = test_df[label].astype(int)

X_train = train_df[features].values
y_train = train_df[label].values

X_test = test_df[features].values
y_test = test_df[label].values   # ← INI AKTUAL DARI EXCEL

# =========================
# TRAIN & PREDICT
# =========================
model = NaiveBayesGaussian()
model.fit(X_train, y_train)

y_pred = model.predict(X_test)

# =========================
# OUTPUT HASIL
# =========================
print("\nHASIL PREDIKSI DATA TESTING (SESUSAI EXCEL):\n")

for i in range(len(y_test)):
    print(f"Baris Excel ke-{i+1}: Prediksi={y_pred[i]} | Aktual={y_test[i]}")

accuracy = np.mean(y_pred == y_test) * 100
print(f"\nAkurasi Model: {accuracy:.2f}%")

print("Jumlah data testing:", len(y_test))
print("Jumlah NaN di target:", test_df["target"].isna().sum())
