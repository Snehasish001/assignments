import math
import matplotlib.pyplot as plt


def constant_hazard_reliability(
    hazard_rate: float,
    time: float
) -> float:

    return math.exp(-hazard_rate * time)


def linear_hazard_reliability(
    k: float,
    time: float
) -> float:

    return math.exp(-(k * time ** 2) / 2)


def weibull_reliability(
    k: float,
    m: float,
    time: float
) -> float:

    return math.exp(
        -(k * time ** (m + 1)) / (m + 1)
    )


def main() -> None:

    # --------------------------------------------------------
    # Input
    # --------------------------------------------------------

    # CASE - I
    lambda_value = 0.3
    case_1_time = 3

    # CASE - II
    k_linear = 0.9
    case_2_time = 5

    # CASE - III
    k_weibull = 0.9
    m_weibull = 0.5
    case_3_time = 5

    # Time values for graph
    times = list(range(1, 11))

    # --------------------------------------------------------
    # CASE - I
    # --------------------------------------------------------

    reliability_case_1 = constant_hazard_reliability(
        lambda_value,
        case_1_time
    )

    # --------------------------------------------------------
    # CASE - II
    # --------------------------------------------------------

    reliability_case_2 = linear_hazard_reliability(
        k_linear,
        case_2_time
    )

    # --------------------------------------------------------
    # CASE - III
    # --------------------------------------------------------

    reliability_case_3 = weibull_reliability(
        k_weibull,
        m_weibull,
        case_3_time
    )

    # --------------------------------------------------------
    # Display Results
    # --------------------------------------------------------

    print("\n--- Software Reliability Results ---")

    print("\nCASE - I : Constant Hazard")
    print(f"Hazard Rate : {lambda_value}")
    print(f"Time : {case_1_time} hour")
    print(f"Reliability : {reliability_case_1:.6f}")

    print("\nCASE - II : Linearly Increasing Hazard")
    print(f"k : {k_linear}")
    print(f"Time : {case_2_time} hour")
    print(f"Reliability : {reliability_case_2:.6f}")

    print("\nCASE - III : Weibull Hazard")
    print(f"k : {k_weibull}")
    print(f"m : {m_weibull}")
    print(f"Time : {case_3_time} hour")
    print(f"Reliability : {reliability_case_3:.6f}")

    # --------------------------------------------------------
    # Reliability Values for Graph
    # --------------------------------------------------------

    reliability_1 = [
        constant_hazard_reliability(
            lambda_value,
            t
        )
        for t in times
    ]

    reliability_2 = [
        linear_hazard_reliability(
            k_linear,
            t
        )
        for t in times
    ]

    reliability_3 = [
        weibull_reliability(
            k_weibull,
            m_weibull,
            t
        )
        for t in times
    ]

    # --------------------------------------------------------
    # Display Reliability Table
    # --------------------------------------------------------

    print("\n--- Reliability vs Time ---")

    print(
        f"{'Time':<8}"
        f"{'Case-I':<15}"
        f"{'Case-II':<15}"
        f"{'Case-III':<15}"
    )

    for i, time in enumerate(times):

        print(
            f"{time:<8}"
            f"{reliability_1[i]:<15.6f}"
            f"{reliability_2[i]:<15.6f}"
            f"{reliability_3[i]:<15.6f}"
        )

    # --------------------------------------------------------
    # Plot
    # --------------------------------------------------------

    plt.figure(figsize=(10, 6))

    plt.plot(
        times,
        reliability_1,
        marker="o",
        label="Case I - Constant Hazard"
    )

    plt.plot(
        times,
        reliability_2,
        marker="o",
        label="Case II - Linear Hazard"
    )

    plt.plot(
        times,
        reliability_3,
        marker="o",
        label="Case III - Weibull"
    )

    plt.xlabel("Time to Failure (hours)")
    plt.ylabel("Reliability")
    plt.title("Software Reliability vs Time to Failure")
    plt.xticks(times)
    plt.grid(True)
    plt.legend()

    plt.show()


if __name__ == "__main__":
    main()