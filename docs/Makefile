# Documentation Makefile for juFFTe (Zensical/MkDocs)

.PHONY: docs docs-serve docs-clean docs-deploy docs-serve-remote help

# MkDocs config is in this directory, content in content/, output in ../site
DOCS_TOOL ?= mkdocs

## Build documentation locally
docs:
	@echo "Building documentation with $(DOCS_TOOL)..."
	@if command -v $(DOCS_TOOL) >/dev/null 2>&1; then \
		$(DOCS_TOOL) build; \
	else \
		echo "Error: $(DOCS_TOOL) not found. Installing..."; \
		pip3 install mkdocs mkdocs-material; \
		mkdocs build; \
	fi
	@echo "✓ Documentation built successfully!"
	@echo "✓ Output: ../site/"
	@echo "✓ View locally: open ../site/index.html"

## Serve documentation locally (development server)
docs-serve:
	@echo "Starting local development server..."
	@echo "✓ Access at: http://localhost:8000"
	@echo "✓ Press Ctrl+C to stop"
	@if command -v $(DOCS_TOOL) >/dev/null 2>&1; then \
		$(DOCS_TOOL) serve; \
	else \
		echo "Error: $(DOCS_TOOL) not found. Installing..."; \
		pip3 install mkdocs mkdocs-material; \
		mkdocs serve; \
	fi

## Serve documentation with remote access (for testing on network)
docs-serve-remote:
	@echo "Starting server accessible from network..."
	@echo "✓ Access at: http://0.0.0.0:8000"
	@if command -v $(DOCS_TOOL) >/dev/null 2>&1; then \
		$(DOCS_TOOL) serve --dev-addr=0.0.0.0:8000; \
	else \
		pip3 install mkdocs mkdocs-material; \
		mkdocs serve --dev-addr=0.0.0.0:8000; \
	fi

## Clean generated documentation
docs-clean:
	@echo "Cleaning documentation..."
	rm -rf ../site/
	rm -rf .mkdocs/
	@echo "✓ Done."

## Deploy to GitHub Pages (requires GitHub CLI or manual push)
docs-deploy: docs
	@echo "Preparing deployment to GitHub Pages..."
	@echo ""
	@echo "Option 1: Automatic (if gh CLI is installed)"
	@echo "  cd .. && gh workflow run docs.yml --ref main"
	@echo ""
	@echo "Option 2: Manual (using git)"
	@echo "  mkdocs gh-deploy"
	@echo ""
	@echo "Option 3: Via GitHub Actions (push to main branch)"
	@echo "  cd .. && git add docs/ && git commit -m 'Update documentation' && git push origin main"
	@echo ""
	@echo "The GitHub Actions workflow will automatically deploy to GitHub Pages."

## Show help
help:
	@echo "juFFTe Documentation Build System (Zensical/MkDocs)"
	@echo ""
	@echo "Local Development:"
	@echo "  make docs          - Build documentation locally"
	@echo "  make docs-serve    - Start local server (http://localhost:8000)"
	@echo "  make docs-serve-remote - Start server on network (0.0.0.0:8000)"
	@echo "  make docs-clean    - Remove generated files"
	@echo ""
	@echo "Deployment:"
	@echo "  make docs-deploy   - Deploy to GitHub Pages (shows options)"
	@echo ""
	@echo "Notes:"
	@echo "  - GitHub Actions auto-deploys on push to main"
	@echo "  - Local builds are in ../site/ directory"
	@echo "  - No external deployment required for local testing"
	@echo ""
	@echo "Prerequisites:"
	@echo "  pip3 install mkdocs mkdocs-material"
