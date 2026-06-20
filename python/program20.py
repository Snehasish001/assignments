def flatten_dict(d, parent_key='', sep='.'):
    result = {}

    for key, value in d.items():
        new_key = parent_key + sep + key if parent_key else key

        if isinstance(value, dict):
            result.update(flatten_dict(value, new_key, sep))
        else:
            result[new_key] = value

    return result


nested = {
    'fullname': 'Alessandra',
    'age': 41,
    'phone-numbers': ['+447421234567', '+447423456789'],
    'residence': {
        'address': {
            'first-line': 'Alexandra Rd',
            'second-line': '',
        },
        'zip': 'N8 0PP',
        'city': 'London',
        'country': 'UK',
    },
}

flat = flatten_dict(nested)

print("Flattened Dictionary:")
for k, v in flat.items():
    print(f"{k} : {v}")