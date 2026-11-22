import random


def exponent(scale_factors: list) -> float:
    return 0.91 + 0.01 * sum(scale_factors)


def effort_to_develop(
    kloc: float,
    scale_factors: list,
    effort_multipliers: list
) -> float:

    e = exponent(scale_factors)

    eaf = 1.0

    for multiplier in effort_multipliers:
        eaf *= multiplier

    return 2.94 * kloc ** e * eaf


def number_of_people(
    effort: float,
    duration_years: float
) -> float:

    duration_months = duration_years * 12

    return effort / duration_months


def main() -> None:

    # --------------------------------------------------------
    # Simulated Input
    # --------------------------------------------------------

    kloc = round(random.uniform(10, 100), 2)

    # Five COCOMO II scale factors
    scale_factors = [
        round(random.uniform(1.0, 5.0), 2)
        for _ in range(5)
    ]

    # Seventeen Post-Architecture cost drivers
    drivers = [
        "RELY",
        "DATA",
        "CPLX",
        "RUSE",
        "DOCU",
        "TIME",
        "STOR",
        "PVOL",
        "ACAP",
        "PCAP",
        "PCON",
        "APEX",
        "PLEX",
        "LTEX",
        "TOOL",
        "SITE",
        "SCED"
    ]

    effort_multipliers = [
        round(random.uniform(0.7, 1.4), 2)
        for _ in range(17)
    ]

    duration = 5

    # --------------------------------------------------------
    # Display Simulated Input
    # --------------------------------------------------------

    print("--- Simulated Input ---")

    print(f"KLOC : {kloc}")

    print("Scale Factors:")

    for i, value in enumerate(scale_factors, 1):
        print(f"SF{i} : {value}")

    print("\nPost-Architecture Cost Drivers:")

    for driver, value in zip(
        drivers,
        effort_multipliers
    ):
        print(f"{driver} : {value}")

    print(f"\nDevelopment Duration : {duration} Years")

    # --------------------------------------------------------
    # Calculations
    # --------------------------------------------------------

    e = exponent(scale_factors)

    effort = effort_to_develop(
        kloc,
        scale_factors,
        effort_multipliers
    )

    people = number_of_people(
        effort,
        duration
    )

    # --------------------------------------------------------
    # Result
    # --------------------------------------------------------

    print("\n--- Post-Architecture Stage Result ---")

    print(f"Scale Factor Sum : {sum(scale_factors):.2f}")
    print(f"Exponent (E)     : {e:.4f}")
    print(f"Effort           : {effort:.2f} Person-Month")
    print(f"Duration         : {duration} Years")
    print(f"Number of People : {people:.2f}")


if __name__ == "__main__":
    main()