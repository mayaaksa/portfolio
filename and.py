import numpy as np

# inisialisasi awal
w1 = -0.3
w2 =  0.1
b  =  0.0
lr =  0.1   # learning rate

# [x1, x2, target]
data = np.array([
    [0, 0, 0],
    [0, 1, 0],
    [1, 0, 0],
    [1, 1, 1],
], dtype=float)

# fungsi aktivasi step
def f(net):
    return 1.0 if net >= 0 else 0.0

# header buat tampilan
print("=" * 70)
print("PERCEPTRON AND")
print(f"  Inisialisasi: w1={w1}, w2={w2}, b={b}, lr={lr}")
print("=" * 70)

max_epoch = 20
converged = False

for epoch in range(1, max_epoch + 1):
    print(f"\n{'─'*70}")
    print(f"  EPOCH {epoch}")
    print(f"{'─'*70}")
    print(f"  {'x1':>4} {'x2':>4} {'Target':>7} {'Net':>8} {'Output':>7} "
          f"{'Error':>6} {'w1':>8} {'w2':>8} {'b':>8}")
    print(f"  {'─'*4} {'─'*4} {'─'*7} {'─'*8} {'─'*7} "
          f"{'─'*6} {'─'*8} {'─'*8} {'─'*8}")

    total_error = 0

    for row in data:
        x1, x2, target = row

        # hitung net
        net = w1 * x1 + w2 * x2 + b

        # fungsi aktivasi
        output = f(net)

        # hitung error
        error = target - output
        total_error += abs(error)

        # update bobot
        w1_new = w1 + lr * error * x1
        w2_new = w2 + lr * error * x2
        b_new  = b  + lr * error

        print(f"  {int(x1):>4} {int(x2):>4} {int(target):>7} {net:>8.4f} "
              f"{int(output):>7} {int(error):>6} "
              f"{w1_new:>8.4f} {w2_new:>8.4f} {b_new:>8.4f}")

        # update
        w1, w2, b = w1_new, w2_new, b_new

    print(f"\n  → total error epoch {epoch}: {int(total_error)}")
    print(f"  → bobot setelah epoch: w1={w1:.4f}, w2={w2:.4f}, b={b:.4f}")

    # cek konvergensi (semua error = 0)
    if total_error == 0:
        print(f"\n  konvergen pada epoch {epoch}, semua output benar.")
        converged = True
        break

if not converged:
    print(f"\n  belum konvergen setelah {max_epoch} epoch.")

# verif akhir
print("\n" + "=" * 70)
print("  VERIFIKASI HASIL AKHIR")
print(f"  Bobot Final: w1={w1:.4f}, w2={w2:.4f}, b={b:.4f}")
print("=" * 70)
print(f"  {'x1':>4} {'x2':>4} {'Target':>7} {'Net':>8} {'Output':>7} {'Status':>8}")
print(f"  {'─'*4} {'─'*4} {'─'*7} {'─'*8} {'─'*7} {'─'*8}")

all_correct = True
for row in data:
    x1, x2, target = row
    net    = w1 * x1 + w2 * x2 + b
    output = f(net)
    status = "benar" if output == target else "salah"
    if output != target:
        all_correct = False
    print(f"  {int(x1):>4} {int(x2):>4} {int(target):>7} {net:>8.4f} "
          f"{int(output):>7} {status:>8}")

print("=" * 70)
if all_correct:
    print("AND benar berhasil dilatih")
else:
    print(" prediksi yang masih salah.")
print("=" * 70)