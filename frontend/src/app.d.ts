// See https://svelte.dev/docs/kit/types#app.d.ts
// for information about these interfaces
declare const __GIT_COMMIT_HASH__: string;
declare const __REPO_URL__: string;
declare const __COMMIT_URL__: string;
declare interface ListBlogItem {
  title: string;
  summary: string;
  author: string;
  time: string | Date;
  tags: string[];
}

declare global {
  namespace App {
    interface Error {}
    // interface Locals {}
    // interface PageData {}
    // interface PageState {}
    // interface Platform {}
  }
}

export {};
