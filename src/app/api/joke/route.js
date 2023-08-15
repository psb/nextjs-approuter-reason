import { handler } from "./handler";

export async function POST(request) {
  return handler(request);
}
