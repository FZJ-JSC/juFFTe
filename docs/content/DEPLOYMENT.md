# GitHub Pages Deployment Guide

## Overview

Documentation is deployed to **GitHub Pages** automatically via GitHub Actions when you push to the `main` branch.

## Automatic Deployment (Recommended)

### Step 1: Enable GitHub Pages

1. Go to your repository on GitHub
2. Navigate to **Settings** → **Pages**
3. Under **Source**, select:
   - **Deploy from a branch**: `gh-pages` (or `main` if using root)
   - **Branch**: `gh-pages`
   - **Folder**: `/ (root)`
4. Click **Save**

### Step 2: Push to Main

When you push changes to `main`:

```bash
git add docs/ mkdocs.yml
git commit -m "Update documentation"
git push origin main
```

The GitHub Actions workflow will:
1. Build the documentation
2. Deploy to GitHub Pages automatically
3. Provide a deployment URL (typically `https://<username>.github.io/<repo>/`)

### Step 3: Access Your Docs

Your documentation will be available at:
```
https://<github-username>.github.io/juFFTe/
```

## Local-Only Development (No Deployment)

If you want to work on documentation without deploying:

### Build Locally

```bash
make docs
```

This creates a `site/` directory with the built HTML.

### Preview Locally

```bash
# Start development server
make docs-serve

# Access at http://localhost:8000
```

The server auto-reloads when you save changes to `.md` files.

### Network Access (Testing on Other Devices)

```bash
make docs-serve-remote

# Access from other devices on your network
# http://<your-local-ip>:8000
```

## Manual Deployment Options

### Option 1: Using GitHub CLI

```bash
# Trigger the workflow manually
gh workflow run docs.yml --ref main
```

### Option 2: Using mkdocs gh-deploy

```bash
# Requires: pip install mkdocs
mkdocs gh-deploy --force
```

This creates/updates the `gh-pages` branch automatically.

### Option 3: Manual Git Push

```bash
# Build first
make docs

# Create gh-pages branch (first time only)
cd site
git init
git add .
git commit -m "Initial documentation build"
git branch -M gh-pages
git remote add origin https://github.com/<username>/juFFTe.git
git push -u origin gh-pages

# Subsequent updates
cd ..
make docs
cd site
git add .
git commit -m "Update documentation"
git push
```

## CI/CD Workflow Details

The `.github/workflows/docs.yml` workflow:

- **Triggers on**: Push to `main`, `develop`, or manual dispatch
- **Builds on**: Ubuntu latest with Python 3.11
- **Installs**: `mkdocs`, `mkdocs-material`, `mkdocs-git-revision-date-localized-plugin`
- **Deploys**: Only on push to `main` branch
- **Environment**: `github-pages` with proper permissions

## Troubleshooting

### Deployment Failed

1. Check GitHub Actions tab for error logs
2. Verify `mkdocs.yml` syntax:
   ```bash
   mkdocs build --strict
   ```
3. Ensure all referenced files exist

### Pages Not Loading

1. Check repository Settings → Pages
2. Verify `gh-pages` branch exists
3. Wait 1-2 minutes after deployment (CDN propagation)

### Local Build Errors

```bash
# Reinstall dependencies
pip3 install --upgrade mkdocs mkdocs-material

# Clean and rebuild
make docs-clean
make docs
```

## Custom Domain (Optional)

To use a custom domain:

1. Add `CNAME` file to `docs/`:
   ```
   docs.juffte.org
   ```

2. Configure DNS:
   ```
   CNAME docs.juffte.org → <username>.github.io
   ```

3. Update repository Settings → Pages → Custom domain

## Security Notes

- GitHub Actions uses `GITHUB_TOKEN` with minimal permissions
- Only `pages: write` and `id-token: write` are granted
- No secrets required for public repositories
- Private repositories require GitHub Pro/Team/Enterprise

## Next Steps

1. **Enable Pages**: Settings → Pages → Select `gh-pages` branch
2. **Test locally**: `make docs-serve`
3. **Push to main**: Automatic deployment
4. **Customize**: Add more pages, examples, and tutorials

Your documentation is now ready for GitHub Pages deployment with full local development support!
