import numpy as np

# Data XOR: x1, x2, target
data = np.array([
    [0, 0, 0],
    [0, 1, 1],
    [1, 0, 1],
    [1, 1, 0]
])

alpha = 0.5

# Bobot awal input ke hidden
w11 = -1
w12 = 0.5
w21 = 1
w22 = -1

# Bias hidden
b1 = 0.5
b2 = 0

# Bobot hidden ke output
v1 = -1
v2 = 0.5

# Bias output
b3 = 1


def aktivasi(net):
    if net >= 0:
        return 1
    else:
        return 0


max_epoch = 10

for epoch in range(1, max_epoch + 1):
    print("\nEPOCH", epoch)
    print("=" * 130)

    # Header tabel
    print(
        f"{'Data':<5}"
        f"{'x1':<5}"
        f"{'x2':<5}"
        f"{'t':<5}"
        f"{'net_h1':<10}"
        f"{'h1':<5}"
        f"{'net_h2':<10}"
        f"{'h2':<5}"
        f"{'net_y':<10}"
        f"{'y':<5}"
        f"{'error':<8}"
        f"{'Update':<10}"
    )

    print("-" * 130)

    total_error = 0

    for i in range(len(data)):
        x1 = data[i][0]
        x2 = data[i][1]
        target = data[i][2]

        # =========================
        # FORWARD PASS MANUAL
        # =========================
        net_h1 = (w11 * x1) + (w12 * x2) + b1
        h1 = aktivasi(net_h1)

        net_h2 = (w21 * x1) + (w22 * x2) + b2
        h2 = aktivasi(net_h2)

        net_y = (v1 * h1) + (v2 * h2) + b3
        y = aktivasi(net_y)

        error = target - y
        total_error += abs(error)

        if error != 0:
            update_status = "Ya"
        else:
            update_status = "Tidak"

        # Cetak baris tabel
        print(
            f"{i + 1:<5}"
            f"{x1:<5}"
            f"{x2:<5}"
            f"{target:<5}"
            f"{net_h1:<10.2f}"
            f"{h1:<5}"
            f"{net_h2:<10.2f}"
            f"{h2:<5}"
            f"{net_y:<10.2f}"
            f"{y:<5}"
            f"{error:<8}"
            f"{update_status:<10}"
        )

        # =========================
        # UPDATE BOBOT MANUAL
        # =========================
        if error != 0:
            w11 = w11 + alpha * error * x1
            w12 = w12 + alpha * error * x2

            w21 = w21 + alpha * error * x1
            w22 = w22 + alpha * error * x2

            b1 = b1 + alpha * error
            b2 = b2 + alpha * error

            v1 = v1 + alpha * error * h1
            v2 = v2 + alpha * error * h2

            b3 = b3 + alpha * error

    print("-" * 130)
    print("Total error epoch", epoch, "=", total_error)

    # Jika semua data sudah benar
    if total_error == 0:
        print("Target sudah tercapai pada epoch ke-", epoch)
        break


# Tabel bobot akhir
print("\nBOBOT AKHIR")
print("=" * 40)
print(f"{'Bobot':<10}{'Nilai':<10}")
print("-" * 40)
print(f"{'w11':<10}{w11:<10.2f}")
print(f"{'w12':<10}{w12:<10.2f}")
print(f"{'w21':<10}{w21:<10.2f}")
print(f"{'w22':<10}{w22:<10.2f}")
print(f"{'b1':<10}{b1:<10.2f}")
print(f"{'b2':<10}{b2:<10.2f}")
print(f"{'v1':<10}{v1:<10.2f}")
print(f"{'v2':<10}{v2:<10.2f}")
print(f"{'b3':<10}{b3:<10.2f}")


# Tabel pengujian akhir
print("\nPENGUJIAN AKHIR")
print("=" * 60)
print(f"{'Data':<5}{'x1':<5}{'x2':<5}{'Target':<10}{'Output':<10}")
print("-" * 60)

for i in range(len(data)):
    x1 = data[i][0]
    x2 = data[i][1]
    target = data[i][2]

    net_h1 = (w11 * x1) + (w12 * x2) + b1
    h1 = aktivasi(net_h1)

    net_h2 = (w21 * x1) + (w22 * x2) + b2
    h2 = aktivasi(net_h2)

    net_y = (v1 * h1) + (v2 * h2) + b3
    y = aktivasi(net_y)

    print(f"{i + 1:<5}{x1:<5}{x2:<5}{target:<10}{y:<10}")