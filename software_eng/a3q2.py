import matplotlib.pyplot as plt


def calculate_failure_data(
    failure_times: list
) -> tuple:

    n = len(failure_times)

    density = []
    cumulative_distribution = []
    reliability = []
    hazard = []

    previous_time = 0

    for i, time in enumerate(failure_times, 1):

        # Length of current operating interval
        delta_time = time - previous_time

        # Probability of failure in this interval
        probability = 1 / n

        # Density function
        f = probability / delta_time

        # Cumulative Distribution Function
        F = i / n

        # Reliability Function
        R = 1 - F

        # Hazard Function
        remaining_components = n - i + 1

        z = 1 / (
            remaining_components * delta_time
        )

        density.append(f)
        cumulative_distribution.append(F)
        reliability.append(R)
        hazard.append(z)

        previous_time = time

    return (
        hazard,
        density,
        cumulative_distribution,
        reliability
    )


def main() -> None:

    # --------------------------------------------------------
    # Failure Data
    # --------------------------------------------------------

    failure_times = [
        8,
        20,
        34,
        46,
        63,
        86,
        111,
        141,
        186,
        266
    ]

    # --------------------------------------------------------
    # Calculations
    # --------------------------------------------------------

    (
        hazard,
        density,
        cumulative_distribution,
        reliability
    ) = calculate_failure_data(
        failure_times
    )

    # --------------------------------------------------------
    # Display Input
    # --------------------------------------------------------

    print("\n--- Failure Data ---")

    for i, time in enumerate(failure_times, 1):

        print(
            f"Failure {i} : "
            f"{time} hour"
        )

    # --------------------------------------------------------
    # Display Results
    # --------------------------------------------------------

    print("\n--- Failure Analysis ---")

    print(
        f"{'Failure':<10}"
        f"{'Time':<10}"
        f"{'Hazard':<15}"
        f"{'Density':<15}"
        f"{'CDF':<15}"
        f"{'Reliability':<15}"
    )

    for i in range(len(failure_times)):

        print(
            f"{i + 1:<10}"
            f"{failure_times[i]:<10}"
            f"{hazard[i]:<15.6f}"
            f"{density[i]:<15.6f}"
            f"{cumulative_distribution[i]:<15.2f}"
            f"{reliability[i]:<15.2f}"
        )

    # --------------------------------------------------------
    # Plot (a) Hazard Function
    # --------------------------------------------------------

    plt.figure(figsize=(9, 5))

    plt.plot(
        failure_times,
        hazard,
        marker="o"
    )

    plt.xlabel("Operating Time (hours)")
    plt.ylabel("Hazard Function z(t)")
    plt.title("Hazard Function vs Operating Time")
    plt.grid(True)

    plt.show()

    # --------------------------------------------------------
    # Plot (b) Density Function
    # --------------------------------------------------------

    plt.figure(figsize=(9, 5))

    plt.plot(
        failure_times,
        density,
        marker="o"
    )

    plt.xlabel("Operating Time (hours)")
    plt.ylabel("Density Function f(t)")
    plt.title("Density Function vs Operating Time")
    plt.grid(True)

    plt.show()

    # --------------------------------------------------------
    # Plot (c) Cumulative Distribution Function
    # --------------------------------------------------------

    plt.figure(figsize=(9, 5))

    plt.step(
        failure_times,
        cumulative_distribution,
        where="post"
    )

    plt.xlabel("Operating Time (hours)")
    plt.ylabel("CDF F(t)")
    plt.title("Cumulative Distribution Function")
    plt.grid(True)

    plt.show()

    # --------------------------------------------------------
    # Plot (d) Reliability Function
    # --------------------------------------------------------

    plt.figure(figsize=(9, 5))

    plt.step(
        failure_times,
        reliability,
        where="post"
    )

    plt.xlabel("Operating Time (hours)")
    plt.ylabel("Reliability R(t)")
    plt.title("Reliability Function")
    plt.grid(True)

    plt.show()


if __name__ == "__main__":
    main()