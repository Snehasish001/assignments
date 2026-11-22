
import random


def type_of_project(KLOC: float) -> str:
    if KLOC < 50:
        return 'Organic'
    elif KLOC < 300:
        return 'Semi-detached'
    else:
        return 'Embedded'


def effort_to_develop(KLOC: float, a: float, b: float, eaf: float = 1.0) -> float:
    return a * KLOC ** b * eaf


def time_to_develop(KLOC: float, a: float, b: float,
                    c: float, d: float, eaf: float = 1.0) -> float:
    effort = effort_to_develop(KLOC, a, b, eaf)
    return c * effort ** d


def number_of_people(KLOC: float, a: float, b: float,
                     c: float, d: float, eaf: float = 1.0) -> float:
    effort = effort_to_develop(KLOC, a, b, eaf)
    time = time_to_develop(KLOC, a, b, c, d, eaf)

    return effort / time


def calculate_eaf(cost_drivers: dict) -> float:

    eaf = 1.0

    for driver, ratings in cost_drivers.items():

        rating = random.choice(list(ratings.keys()))

        print(f"{driver} : {rating}")

        eaf *= ratings[rating]

    return eaf


def main() -> None:

    # a, b, c, d
    constant_factors = {
        'Organic': [2.4, 1.05, 2.5, 0.38],
        'Semi-detached': [3.0, 1.12, 2.5, 0.35],
        'Embedded': [3.6, 1.20, 2.5, 0.32]
    }

    # Intermediate COCOMO Cost Drivers
    #
    # Values are Effort Multipliers.
    cost_drivers = {

        "RELY": {
            "Very Low": 0.75,
            "Low": 0.88,
            "Nominal": 1.00,
            "High": 1.15,
            "Very High": 1.40
        },

        "DATA": {
            "Low": 0.94,
            "Nominal": 1.00,
            "High": 1.08,
            "Very High": 1.16
        },

        "CPLX": {
            "Very Low": 0.70,
            "Low": 0.85,
            "Nominal": 1.00,
            "High": 1.15,
            "Very High": 1.30,
            "Extra High": 1.65
        },

        "TIME": {
            "Nominal": 1.00,
            "High": 1.11,
            "Very High": 1.30,
            "Extra High": 1.66
        },

        "STOR": {
            "Nominal": 1.00,
            "High": 1.06,
            "Very High": 1.21,
            "Extra High": 1.56
        },

        "VIRT": {
            "Low": 0.87,
            "Nominal": 1.00,
            "High": 1.15,
            "Very High": 1.30
        },

        "TURN": {
            "Low": 0.87,
            "Nominal": 1.00,
            "High": 1.07,
            "Very High": 1.15
        },

        "ACAP": {
            "Very Low": 1.46,
            "Low": 1.19,
            "Nominal": 1.00,
            "High": 0.86,
            "Very High": 0.71
        },

        "AEXP": {
            "Very Low": 1.29,
            "Low": 1.13,
            "Nominal": 1.00,
            "High": 0.91,
            "Very High": 0.82
        },

        "PCAP": {
            "Very Low": 1.42,
            "Low": 1.17,
            "Nominal": 1.00,
            "High": 0.86,
            "Very High": 0.70
        },

        "VEXP": {
            "Very Low": 1.21,
            "Low": 1.10,
            "Nominal": 1.00,
            "High": 0.90,
            "Very High": 0.78
        },

        "LEXP": {
            "Very Low": 1.14,
            "Low": 1.07,
            "Nominal": 1.00,
            "High": 0.95,
            "Very High": 0.85
        },

        "MODP": {
            "Very Low": 1.24,
            "Low": 1.10,
            "Nominal": 1.00,
            "High": 0.91,
            "Very High": 0.82
        },

        "TOOL": {
            "Very Low": 1.24,
            "Low": 1.10,
            "Nominal": 1.00,
            "High": 0.91,
            "Very High": 0.83
        },

        "SCED": {
            "Very Low": 1.23,
            "Low": 1.08,
            "Nominal": 1.00,
            "High": 1.04,
            "Very High": 1.10
        }
    }

    # Generate random KLOC
    KLOC = random.uniform(1, 500)

    print(f"Generated KLOC : {KLOC:.2f}")

    project_type = type_of_project(KLOC)

    print(f"\nType of project : {project_type}")

    a, b, c, d = constant_factors[project_type]

    # Calculate EAF using 15 cost drivers
    print("\n--- Cost Drivers ---")

    eaf = calculate_eaf(cost_drivers)

    # Intermediate COCOMO calculations
    effort = effort_to_develop(KLOC, a, b, eaf)

    time = time_to_develop(
        KLOC,
        a,
        b,
        c,
        d,
        eaf
    )

    people = number_of_people(
        KLOC,
        a,
        b,
        c,
        d,
        eaf
    )

    print("\n--- Intermediate COCOMO Result ---")

    print(f"EAF              : {eaf:.4f}")
    print(f"Effort           : {effort:.2f} Person-Month")
    print(f"Development Time : {time:.2f} Months")
    print(f"Number of People : {people:.2f}")


if __name__ == "__main__":
    main()
