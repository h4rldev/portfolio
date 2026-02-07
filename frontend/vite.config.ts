import devtoolsJson from 'vite-plugin-devtools-json';
import tailwindcss from '@tailwindcss/vite';
import { sveltekit } from '@sveltejs/kit/vite';
import { defineConfig } from 'vite';
import { execSync } from 'child_process';

// Get the current Git commit hash
const getGitCommitHash = () => {
  try {
    return execSync('git rev-parse --short HEAD').toString().trim();
  } catch (e) {
    return 'unknown';
  }
};

const commitHash = getGitCommitHash();
const repoUrl = 'https://github.com/h4rldev/portfolio'; // Change this
const commitLink = `${repoUrl}/commit/${commitHash}`;
const commitTreeLink = `${repoUrl}/tree/${commitHash}`;

export default defineConfig({
  define: {
    __GIT_COMMIT_HASH__: JSON.stringify(commitHash),
    __COMMIT_URL__: JSON.stringify(commitLink),
    __REPO_URL__: JSON.stringify(commitTreeLink),
  },
	plugins: [
		tailwindcss(),
		sveltekit(),
		devtoolsJson(),
	]
});
