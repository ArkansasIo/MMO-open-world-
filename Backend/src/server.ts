import Fastify from "fastify";
import { z } from "zod";

const app = Fastify({ logger: true, bodyLimit: 64 * 1024 });
const HealthResponse = z.object({ status: z.literal("ok"), service: z.literal("etherroad-control-plane") });

app.get("/health", async (_request, reply) => {
  const payload = { status: "ok" as const, service: "etherroad-control-plane" as const };
  return reply.code(200).send(HealthResponse.parse(payload));
});

app.get("/v1/realms", async () => ({
  realms: [
    { id: "realm-prototype-01", name: "Etherroad Prototype", region: "local", status: "development" }
  ],
  note: "Prototype directory only; production health registry and capacity-aware discovery are not implemented."
}));

const SessionRequest = z.object({
  accountId: z.string().min(1).max(128),
  characterId: z.string().min(1).max(128),
  realmId: z.string().min(1).max(128)
});

app.post("/v1/sessions", async (request, reply) => {
  const parsed = SessionRequest.safeParse(request.body);
  if (!parsed.success) {
    return reply.code(400).send({ error: "invalid_request", details: parsed.error.flatten() });
  }

  // Deliberately fail closed: never return an unsigned or fake join ticket.
  return reply.code(503).send({
    error: "session_allocator_unavailable",
    message: "Session allocation requires identity verification, process leases, capacity checks, and signed single-use join tickets."
  });
});

const port = Number(process.env.PORT ?? 8080);
const host = process.env.HOST ?? "0.0.0.0";

try {
  await app.listen({ port, host });
} catch (error) {
  app.log.error(error);
  process.exitCode = 1;
}
