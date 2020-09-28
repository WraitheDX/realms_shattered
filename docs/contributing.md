# Contribute

**Opening new issue?** Please read [issues.md](issues.md) first.

We aim to keep contributing to Shattered Realms as simple as possible, but to achieve this does mean we all need to go the extra mile with consistent naming, commenting, and formatting.

## Managing branches

There are a couple of guidelines we suggest sticking to:

* Add this repository as an `upstream` remote.
* Keep your `master` branch clean. This means you can easily pull changes made to this repository into yours.
* Create a new branch for each new feature or set of related bug fixes.
* Never merge from your local branches into your `master` branch. Only update that by pulling from `upstream/master`.

## Code Style

See [code_style](code_style_guide.md) for details.

## Commenting

Extensive documentation of classes and class members will make the code more readable to new contributors.

See [comment_style_guide](comment_style_guide.md) for details.

## Naming Conventions

Clear naming conventions can greatly reduce the time it takes to decipher code, and reduce the size of comments.

1. Declare class names with first letter of each word capitalized.
2. Declare function and variable names entirely lowercase with underscores '_' between each word.
3. Declare constants in all caps.
4. Make names specific and avoid abbreviations, but also avoid absurdly long names.
5. Order the wording from most refined to the broadest.
			Ex: A creature will have two health variables: their current health, and their maximum health.
					If we have it set up as current_health and max_health, typing in current or max could give us: current_health, current_mana, current_entities_in_map, current_time, current_temperature, etc...
					Having them set up as health_current and health_max ensures that if we know we need something to do with health, typing in health should give us most possibilities.
