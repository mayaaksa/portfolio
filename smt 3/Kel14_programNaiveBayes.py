import pandas as pd
import math

# ===============================
# FILE & KONFIGURASI
# ===============================
FILE_TRAIN = "Kel 14_DataTraining.xlsx"
FILE_TEST  = "Kel 14_DataTesting.xlsx"
LABEL_COL  = "target"

NUMERIK = [
    "age",
    "trestbps",
    "chol",
    "thalach",
    "oldpeak"
]

KATEGORIKAL = [
    "sex",
    "cp",
    "fbs",
    "restecg",
    "exang",
    "slope",
    "ca",
    "thal"
]

KETERANGAN_NUMERIK = {
    "age": "Usia pasien (tahun)",
    "trestbps": "Tekanan darah saat istirahat (mm Hg)",
    "chol": "Kadar kolesterol (mg/dl)",
    "thalach": "Detak jantung maksimum",
    "oldpeak": "Depresi ST"
}

KETERANGAN_KATEGORIKAL = {
    "sex": {
        "judul": "Jenis Kelamin",
        "opsi": {
            "0": "Perempuan",
            "1": "Laki-laki"
        }
    },
    "cp": {
        "judul": "Jenis Nyeri Dada",
        "opsi": {
            "0": "Typical Angina",
            "1": "Atypical Angina",
            "2": "Non-anginal Pain",
            "3": "Asymptomatic"
        }
    },
    "fbs": {
        "judul": "Gula Darah Puasa",
        "opsi": {
            "0": "≤ 120 mg/dl",
            "1": "> 120 mg/dl"
        }
    },
    "restecg": {
        "judul": "Hasil ECG Istirahat",
        "opsi": {
            "0": "Normal",
            "1": "ST-T wave abnormality",
            "2": "Left ventricular hypertrophy"
        }
    },
    "exang": {
        "judul": "Nyeri Dada Saat Olahraga",
        "opsi": {
            "0": "Tidak",
            "1": "Ya"
        }
    },
    "slope": {
        "judul": "Kemiringan Segmen ST",
        "opsi": {
            "0": "Upsloping",
            "1": "Flat",
            "2": "Downsloping"
        }
    },
    "ca": {
        "judul": "Jumlah Pembuluh Besar",
        "opsi": {
            "0": "0 pembuluh",
            "1": "1 pembuluh",
            "2": "2 pembuluh",
            "3": "3 pembuluh"
        }
    },
    "thal": {
        "judul": "Status Thalassemia",
        "opsi": {
            "1": "Normal",
            "2": "Fixed Defect",
            "3": "Reversible Defect"
        }
    }
}

# ===============================
# LOAD XLSX
# ===============================
def load_excel(filename):
    df = pd.read_excel(filename)
    return df.to_dict(orient="records")

# ===============================
# TRAIN NAIVE BAYES
# ===============================
def train_naive_bayes(data):
    model = {}
    classes = set(d[LABEL_COL] for d in data)

    # PRIOR
    model["prior"] = {}
    total = len(data)
    for c in classes:
        model["prior"][c] = sum(1 for d in data if d[LABEL_COL] == c) / total

    # KATEGORIKAL
    model["cat"] = {}
    for c in classes:
        model["cat"][c] = {}
        class_data = [d for d in data if d[LABEL_COL] == c]

        for attr in KATEGORIKAL:
            model["cat"][c][attr] = {}
            values = set(d[attr] for d in data)

            for v in values:
                count = sum(1 for d in class_data if d[attr] == v)
                model["cat"][c][attr][v] = count / len(class_data)

    # NUMERIK (GAUSSIAN)
    model["num"] = {}
    for c in classes:
        model["num"][c] = {}
        class_data = [d for d in data if d[LABEL_COL] == c]

        for attr in NUMERIK:
            vals = [float(d[attr]) for d in class_data]
            mean = sum(vals) / len(vals)
            var = sum((x - mean) ** 2 for x in vals) / len(vals)
            model["num"][c][attr] = (mean, var)

    return model, classes

# ===============================
# GAUSSIAN
# ===============================
def gaussian(x, mean, var):
    if var == 0:
        return 0
    return (1 / math.sqrt(2 * math.pi * var)) * \
           math.exp(-((x - mean) ** 2) / (2 * var))

# ===============================
# PREDIKSI 1 DATA
# ===============================
def predict(data, model, classes):
    probs = {}

    for c in classes:
        prob = model["prior"][c]

        for attr in KATEGORIKAL:
            prob *= model["cat"][c][attr].get(data[attr], 1e-6)

        for attr in NUMERIK:
            mean, var = model["num"][c][attr]
            prob *= gaussian(float(data[attr]), mean, var)

        probs[c] = prob

    return max(probs, key=probs.get), probs

# ===============================
# EVALUASI DATA TESTING
# ===============================
def evaluasi(test_data, model, classes):
    TP = TN = FP = FN = 0

    print("\nHasil Prediksi Data Testing:\n")

    for i, d in enumerate(test_data, start=1):
        pred, _ = predict(d, model, classes)
        actual = d[LABEL_COL]

        pred = int(pred)
        actual = int(actual)

        print(f"Data ke-{i}: Prediksi={pred} | Aktual={actual}")

        if pred == 1 and actual == 1:
            TP += 1
        elif pred == 0 and actual == 0:
            TN += 1
        elif pred == 1 and actual == 0:
            FP += 1
        elif pred == 0 and actual == 1:
            FN += 1

    total = TP + TN + FP + FN

    if total == 0:
        print("\nTidak ada data yang berhasil dievaluasi.")
        return

    acc = (TP + TN) / total * 100

    print("\n=== CONFUSION MATRIX ===")
    print(f"TP: {TP}   FP: {FP}")
    print(f"FN: {FN}   TN: {TN}")
    print(f"Akurasi: {acc:.4f} %")

    print("\n=== PRIOR PROBABILITY ===")
    for c in model["prior"]:
        print(f"P(target={c}) = {model['prior'][c]:.4f}")

# ===============================
# MAIN
# ===============================
def main():
    train_data = load_excel(FILE_TRAIN)
    test_data  = load_excel(FILE_TEST)


    model, classes = train_naive_bayes(train_data)

    while True:
        print("\n==============================")
        print("MENU NAIVE BAYES")
        print("==============================")
        print("1. Evaluasi Data Testing (CSV)")
        print("2. Prediksi Data Manual")
        print("3. Keluar")

        pilih = input("Pilih menu: ")

        if pilih == "1":
            evaluasi(test_data, model, classes)

        elif pilih == "2":
            input_data = {}
            print("\nInput Data:")

            print("\n=== INPUT DATA KATEGORIKAL ===")
            for attr in KATEGORIKAL:
                info = KETERANGAN_KATEGORIKAL[attr]
                print(f"\n{attr} - {info['judul']}")
                for k, v in info["opsi"].items():
                    print(f"{k} = {v}")
                input_data[attr] = input("Pilih: ")

            print("\n=== INPUT DATA NUMERIK ===")
            for attr in NUMERIK:
                print(f"{attr} ({KETERANGAN_NUMERIK[attr]})")
                input_data[attr] = input("Masukkan nilai: ")

            pred, probs = predict(input_data, model, classes)

            print("\n=== HASIL ===")
            for c, p in probs.items():
                print(f"Probabilitas target={c}: {p:.6e}")

            print(f"\nKEPUTUSAN: target={pred}")

        elif pilih == "3":
            print("\nProgram selesai.")
            break

        else:
            print("Menu tidak valid!")

# ===============================
main()