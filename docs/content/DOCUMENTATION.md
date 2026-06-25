# Documentation Tooling for juFFTe

This directory contains the documentation infrastructure for juFFTe, configured for **Zensical** (or MkDocs with Material theme).

## Overview

The documentation uses **Zensical** (a modern static site generator built by the creators of Material for MkDocs) for generating professional, searchable documentation.

## Prerequisites

Install the required tools:

```bash
# Install MkDocs and Material theme (Zensical-compatible)
pip install mkdocs mkdocs-material mkdocstrings

# Or install Zensical directly (when available)
pip install zensical
```

## Building Documentation

```bash
# Using MkDocs (compatible with Zensical config)
mkdocs build

# Using Zensical (when CLI is stable)
zensical build

# Or with the Makefile target
make docs
```

## Preview Locally

```bash
# Start development server
mkdocs serve

# Or
zensical serve

# Access at http://localhost:8000
```

## Documentation Structure

```
docs/
├── index.md              # Main landing page
├── tutorials/            # Step-by-step guides
│   └── getting-started.md
├── api/                  # API reference
│   └── index.md
├── examples/             # Code examples
│   └── simple-1d-fft.md
└── assets/               # Images, logos, etc.
```

## Configuration

The `mkdocs.yml` file in the project root configures:

- **Material theme** with dark/light mode
- **Navigation structure**
- **Search functionality**
- **Syntax highlighting**
- **Git revision dates**
- **Version management** (via `mike`)

## Deploying

### GitLab Pages

Documentation is automatically deployed via `.github/workflows/docs.yml`:

1. Build runs on push to `main`
2. Deploy to GitLab Pages or GitHub Pages
3. Available at `https://juffte.gitlab.io`

### Zensical Hosting

When ready to use Zensical hosting:

1. Configure `zensical.yaml` with your project details
2. Deploy via Zensical CLI or web interface
3. Custom domain: `juffte.zensical.io`

## Adding Documentation

### New Pages

1. Create `.md` file in appropriate directory
2. Add to `nav` section in `mkdocs.yml`
3. Write content using Markdown

### API Documentation

For Fortran API docs, we recommend:

1. Add FORD-style comments to source code
2. Use `mkdocstrings` with Fortran plugin (when available)
3. Or maintain manual API reference in `docs/api/`

## Maintenance

- Keep examples in sync with API changes
- Update version in `mkdocs.yml` for releases
- Review search analytics (if enabled)
- Test on mobile devices

## Migration to Zensical

When Zensical CLI becomes stable:

1. Replace `mkdocs.yml` with `zensical.yaml`
2. Update build commands in CI/CD
3. Test all features
4. Deploy

The current MkDocs setup is **fully compatible** with Zensical's configuration format.

## Support

- Documentation issues: [GitLab Issues](https://gitlab.com/nval/juFFTe/-/issues)
- Zensical docs: https://zensical.org/docs/
