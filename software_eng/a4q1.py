import matplotlib.pyplot as plt


# Failure data
time = [1000, 2000, 3000, 4000, 5000, 6000]
failures = [59, 24, 29, 30, 17, 13]

total = sum(failures)

# Number of components surviving at beginning of each interval
survivors = []
remaining = total

for failure in failures:
    survivors.append(remaining)
    remaining -= failure


# Calculate values
density = []
cdf = []
reliability = []
hazard = []

failed = 0

for i in range(len(failures)):

    failed += failures[i]

    # f(t)
    f = failures[i] / (total * 1000)

    # F(t)
    F = failed / total

    # R(t)
    R = 1 - F

    # z(t)
    z = failures[i] / (survivors[i] * 1000)

    density.append(f)
    cdf.append(F)
    reliability.append(R)
    hazard.append(z)


# Display table
print("\nTime\tFailure\tHazard\t\tDensity\t\tCDF\t\tReliability")

for i in range(len(time)):
    print(
        time[i],
        "\t",
        failures[i],
        "\t",
        round(hazard[i], 6),
        "\t",
        round(density[i], 6),
        "\t",
        round(cdf[i], 6),
        "\t",
        round(reliability[i], 6)
    )


# ---------------------------------------------------------
# Plot Hazard Function
# ---------------------------------------------------------

plt.figure()

plt.plot(time, hazard, marker="o")

plt.xlabel("Time")
plt.ylabel("z(t)")
plt.title("Hazard Function")

plt.grid()
plt.show()


# ---------------------------------------------------------
# Plot Density Function
# ---------------------------------------------------------

plt.figure()

plt.plot(time, density, marker="o")

plt.xlabel("Time")
plt.ylabel("f(t)")
plt.title("Density Function")

plt.grid()
plt.show()


# ---------------------------------------------------------
# Plot Cumulative Distribution Function
# ---------------------------------------------------------

plt.figure()

plt.plot(time, cdf, marker="o")

plt.xlabel("Time")
plt.ylabel("F(t)")
plt.title("Cumulative Distribution Function")

plt.grid()
plt.show()


# ---------------------------------------------------------
# Plot Reliability Function
# ---------------------------------------------------------

plt.figure()

plt.plot(time, reliability, marker="o")

plt.xlabel("Time")
plt.ylabel("R(t)")
plt.title("Reliability Function")

plt.grid()
plt.show()