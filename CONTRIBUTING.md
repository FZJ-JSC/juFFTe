<!--
SPDX-FileCopyrightText: juFFTe developers
SPDX-License-Identifier: Apache-2.0
-->

# Contributing to juFFTe

Thank you for your interest in contributing to juFFTe.

This document defines who the **juFFTe developers** are, who maintains the project, and how contributions are accepted.

## juFFTe developers

The term **juFFTe developers** refers collectively to all people and organizations whose contributions have been accepted into the juFFTe repository.

This includes contributors of source code, tests, documentation, build-system changes, examples, benchmarks, generated kernels, and other project material.

The file-level copyright statement

```text
SPDX-FileCopyrightText: juFFTe developers
```

is used as a collective project copyright notice. Individual authorship is recorded through the Git history.

## Maintainers

Maintainers are responsible for reviewing contributions, guiding the technical direction of the project, and deciding whether changes are accepted.

Current maintainers:

- Kaveh Haghighi Mood <k.haghighi.mood@fz-juelich.de>
- Daniel Seibel <d.seibel@fz-juelich.de>

## How to contribute

Contributions should normally be submitted as pull requests.

Before submitting a pull request, please make sure that:

* the change is focused;
* the code builds;
* relevant tests are added or updated when practical;
* existing tests still pass;
* new files contain REUSE/SPDX license headers;
* commits are signed off according to the DCO section below.

For larger changes, please open an issue or discussion first so that the design can be discussed before substantial work is done.

## License policy

juFFTe is licensed under the Apache License, Version 2.0.

Source files should use REUSE/SPDX headers. For most files this means:

```text
SPDX-FileCopyrightText: juFFTe developers
SPDX-License-Identifier: Apache-2.0
```

The exact comment syntax depends on the file type. For example, Fortran files should use `!`, C and header files should use `//`, and Makefiles or Python files should use `#`.

License texts are stored in the `LICENSES/` directory.

## Developer Certificate of Origin

juFFTe uses the [Developer Certificate of Origin](https://en.wikipedia.org/wiki/Developer_Certificate_of_Origin), [Version 1.1](https://developercertificate.org/).

By contributing to juFFTe, you certify that you have the right to submit the contribution under the project license. This is done by adding a `Signed-off-by` line to every commit message.

The sign-off line has the form:

```text
Signed-off-by: Full Name <email@example.org>
```

You can add it automatically when committing with Git:

```sh
git commit -s
```

If you already made a commit without the sign-off, you can amend the latest commit with:

```sh
git commit --amend -s
```

Pull requests with unsigned commits may be rejected until the required sign-offs are added.
