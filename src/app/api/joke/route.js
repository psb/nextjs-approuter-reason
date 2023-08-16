import { handler } from "@/reason_output/src/reason_src/api/joke_handler";

export async function POST(request) {
  return handler(request);
}
